//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_SQSDATABASETEST_H
#define AWMOCK_CORE_SQSDATABASETEST_H

// GTest includes
#include <gtest/gtest.h>

// Poco includes
#include "Poco/Path.h"

// Local includes
#include <awsmock/core/Configuration.h>
#include <awsmock/db/SQSDatabase.h>

#define CONFIG_FILE "/tmp/aws-mock.properties"
#define REGION "eu-central-1"
#define QUEUE "test-QUEUE"
#define QUEUE_URL "http://localhost:4567/000000000000/test-QUEUE"
#define BODY "{\"TestObject\": \"TestValue\"}"
#define OWNER "test-owner"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    class SQSDatabaseTest : public ::testing::Test {

    protected:

      void SetUp() override {
          _region = _configuration.getString("awsmock.region");
      }

      void TearDown() override {
          _sqsDatabase.DeleteAllQueues();
          _sqsDatabase.DeleteAllMessages();
      }

      std::string _region;
      Core::Configuration _configuration = Core::Configuration(CONFIG_FILE);
      SQSDatabase _sqsDatabase = SQSDatabase(_configuration);
    };

    TEST_F(SQSDatabaseTest, QueueCreateTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};

        // act
        Entity::SQS::Queue result = _sqsDatabase.CreateQueue(queue);

        // assert
        EXPECT_TRUE(result.name == QUEUE);
        EXPECT_TRUE(result.region == REGION);
    }

    TEST_F(SQSDatabaseTest, QueueListTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);

        // act
        Entity::SQS::QueueList result = _sqsDatabase.ListQueues(queue.region);

        // assert
        EXPECT_EQ(result.size(), 1);
    }

    TEST_F(SQSDatabaseTest, MessageCreateTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);
        Entity::SQS::Message message = {.queueUrl=queue.name, .body=BODY,};

        // act
        Entity::SQS::Message result = _sqsDatabase.CreateMessage(message);

        // assert
        EXPECT_FALSE(result.oid.empty());
        EXPECT_TRUE(result.body == BODY);
    }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_SQSDATABASETEST_H