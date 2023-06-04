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
      }

      void TearDown() override {
          try {
              Poco::Data::Statement stmt(_session);
              stmt << "DELETE FROM sqs_attribute;"
                      "DELETE FROM sqs_message;"
                      "DELETE FROM sqs_queue;", now;
          } catch(Poco::Exception &exc){
              std::cerr << exc.message() << std::endl;
          }
      }

      Core::Configuration _configuration = Core::Configuration("/tmp/aws-mock.properties");
      SQSDatabase _database = SQSDatabase(_configuration);
      Poco::Data::Session _session = _database.GetSession();
    };

    TEST_F(SQSDatabaseTest, ConstructorTest) {

        // arrange
        int count = 0;

        // act
        _session << "SELECT COUNT(*) FROM sqs_queue", into(count), now;

        // assert
        EXPECT_EQ(count, 0);
    }

    TEST_F(SQSDatabaseTest, QueueCreateTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .url=QUEUE_URL};

        // act
        Entity::SQS::Queue result = _database.CreateQueue(queue);

        // assert
        EXPECT_TRUE(result.name == QUEUE);
        EXPECT_TRUE(result.region == REGION);
    }

    TEST_F(SQSDatabaseTest, QueueListTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .url=QUEUE_URL};
        queue = _database.CreateQueue(queue);

        // act
        Entity::SQS::QueueList result = _database.ListQueues(queue.region);

        // assert
        EXPECT_EQ(result.size(), 1);
    }

    TEST_F(SQSDatabaseTest, MessageCreateTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .url=QUEUE_URL};
        queue = _database.CreateQueue(queue);
        Entity::SQS::Message message = {.queue=queue.name, .body=BODY,};

        // act
        Entity::SQS::Message result = _database.CreateMessage(message);

        // assert
        EXPECT_GT(result.id, 0);
        EXPECT_TRUE(result.body == BODY);
    }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_SQSDATABASETEST_H