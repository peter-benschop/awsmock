//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_SQSSERVICETEST_H
#define AWMOCK_CORE_SQSSERVICETEST_H

// GTest includes
#include <gtest/gtest.h>

// Poco includes
#include "Poco/Path.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/db/SQSDatabase.h>
#include <awsmock/service/SQSService.h>

#define REGION "eu-central-1"
#define QUEUE "test-queue"
#define QUEUE_URL "http://localhost:4567/000000000000/test-queue"
#define BODY "{\"TestObject\": \"TestValue\"}"
#define OWNER "test-owner"

namespace AwsMock::Service {

    using namespace Poco::Data::Keywords;

    class SQSServiceTest : public ::testing::Test {

    protected:

      void SetUp() override {
      }

      void TearDown() override {
          try {
              Poco::Data::Statement stmt(_session);
              stmt << "DELETE FROM sqs_queue_attribute;"
                      "DELETE FROM sqs_message_attribute;"
                      "DELETE FROM sqs_message;"
                      "DELETE FROM sqs_queue;", now;
          } catch(Poco::Exception &exc){
              std::cerr << exc.message() << std::endl;
          }
      }

      Core::Configuration _configuration = Core::Configuration("/tmp/aws-mock.properties");
      Database::SQSDatabase _database = Database::SQSDatabase(_configuration);
      SQSService _service = SQSService(_configuration);
      Poco::Data::Session _session = _database.GetSession();
    };

    TEST_F(SQSServiceTest, QueueCreateTest) {

        // arrange
        Dto::SQS::CreateQueueRequest request = {.region=REGION, .name=QUEUE, .queueUrl=QUEUE_URL, .owner=OWNER};

        // act
        Dto::SQS::CreateQueueResponse response = _service.CreateQueue(request);

        // assert
        EXPECT_TRUE(response.name == QUEUE);
        EXPECT_TRUE(response.region == REGION);
    }

    TEST_F(SQSServiceTest, QueueCreateAttributeTest) {

        // arrange
        Dto::SQS::CreateQueueRequest request = {.region=REGION, .name=QUEUE, .queueUrl=QUEUE_URL, .owner=OWNER};

        // act
        Dto::SQS::CreateQueueResponse response = _service.CreateQueue(request);
        Database::Entity::SQS::QueueAttribute attributes = _database.GetQueueAttributesByQueueUrl(response.url);

        // assert
        EXPECT_TRUE(response.name == QUEUE);
        EXPECT_TRUE(response.region == REGION);
        EXPECT_EQ(attributes.maxMessageSize, 262144);
        EXPECT_EQ(attributes.visibilityTimeout, 30);
    }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_SQSSERVICETEST_H