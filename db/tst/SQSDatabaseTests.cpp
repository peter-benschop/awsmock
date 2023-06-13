//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_SQSDATABASETEST_H
#define AWMOCK_CORE_SQSDATABASETEST_H

// GTest includes
#include <gtest/gtest.h>

// Poco includes
#include "Poco/Path.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/AwsUtils.h>
#include <awsmock/db/SQSDatabase.h>

#define CONFIG_FILE "/tmp/aws-mock.properties"

#define QUEUE "test-queue"
#define QUEUE_URL "http://localhost:4567/000000000000/test-queue"
#define BODY "{\"TestObject\": \"TestValue\"}"
#define OWNER "test-owner"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    class SQSDatabaseTest : public ::testing::Test {

    protected:

      void SetUp() override {
          _region = _configuration.getString("awsmock.region");
          _queueArn = Core::AwsUtils::CreateSQSQueueArn(_region, Core::AwsUtils::GetDefaultAccountId(), QUEUE);
      }

      void TearDown() override {
          _sqsDatabase.DeleteAllQueues();
          _sqsDatabase.DeleteAllMessages();
      }

      std::string _region, _queueArn;
      Core::Configuration _configuration = Core::Configuration(CONFIG_FILE);
      SQSDatabase _sqsDatabase = SQSDatabase(_configuration);
    };

    TEST_F(SQSDatabaseTest, QueueCreateTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL, .queueArn=_queueArn};

        // act
        Entity::SQS::Queue result = _sqsDatabase.CreateQueue(queue);

        // assert
        EXPECT_TRUE(result.name == QUEUE);
        EXPECT_TRUE(result.region == _region);
    }

    TEST_F(SQSDatabaseTest, QueueByIdTest) {

        // arrange
        Entity::SQS::Queue queue = _sqsDatabase.CreateQueue({.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL, .queueArn=_queueArn});

        // act
        Entity::SQS::Queue result = _sqsDatabase.GetQueueById(queue.oid);

        // assert
        EXPECT_TRUE(result.name == QUEUE);
        EXPECT_TRUE(result.region == _region);
    }

    TEST_F(SQSDatabaseTest, QueueByArnTest) {

        // arrange
        Entity::SQS::Queue queue = _sqsDatabase.CreateQueue({.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL, .queueArn=_queueArn});

        // act
        Entity::SQS::Queue result = _sqsDatabase.GetQueueByArn(queue.queueArn);

        // assert
        EXPECT_TRUE(result.name == QUEUE);
        EXPECT_TRUE(result.region == _region);
    }

    TEST_F(SQSDatabaseTest, QueueListTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);

        // act
        Entity::SQS::QueueList result = _sqsDatabase.ListQueues(queue.region);

        // assert
        EXPECT_EQ(result.size(), 1);
    }

    TEST_F(SQSDatabaseTest, QueuePurgeTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);
        Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
        _sqsDatabase.CreateMessage(message);

        // act
        _sqsDatabase.PurgeQueue(queue.region, queue.queueUrl);
        long result = _sqsDatabase.CountMessages(queue.region, queue.queueUrl);

        // assert
        EXPECT_EQ(0, result);
    }

    TEST_F(SQSDatabaseTest, QueueDeleteTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);

        // act
        _sqsDatabase.DeleteQueue(queue);
        bool result = _sqsDatabase.QueueExists(queue.region, queue.queueUrl);

        // assert
        EXPECT_FALSE(result);
    }

    TEST_F(SQSDatabaseTest, MessageCreateTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);
        Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};

        // act
        Entity::SQS::Message result = _sqsDatabase.CreateMessage(message);

        // assert
        EXPECT_FALSE(result.oid.empty());
        EXPECT_TRUE(result.body == BODY);
    }

    TEST_F(SQSDatabaseTest, MessageReceiveTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);
        Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
        _sqsDatabase.CreateMessage(message);

        // act
        Entity::SQS::MessageList messageList;
        _sqsDatabase.ReceiveMessages(_region, QUEUE, messageList);

        // assert
        EXPECT_FALSE(messageList.empty());
    }

    TEST_F(SQSDatabaseTest, MessageCountTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);
        Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
        _sqsDatabase.CreateMessage(message);

        // act
        long result = _sqsDatabase.CountMessages(_region, QUEUE);

        // assert
        EXPECT_EQ(1, result);
    }

    TEST_F(SQSDatabaseTest, MessageCountStatusTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);
        Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
        _sqsDatabase.CreateMessage(message);

        // act
        long result = _sqsDatabase.CountMessagesByStatus(_region, QUEUE, Entity::SQS::INITIAL);

        // assert
        EXPECT_EQ(1, result);
    }

    TEST_F(SQSDatabaseTest, MessageResetTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);
        Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
        _sqsDatabase.CreateMessage(message);
        Entity::SQS::MessageList messageList;
        _sqsDatabase.ReceiveMessages(_region, QUEUE, messageList);
        Poco::Thread().sleep(1000);

        // act
        _sqsDatabase.ResetMessages(QUEUE, 1);
        long result = _sqsDatabase.CountMessagesByStatus(_region, QUEUE, Entity::SQS::INITIAL);

        // assert
        EXPECT_EQ(1, result);
    }

    TEST_F(SQSDatabaseTest, MessageGetByReceiptHandleTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);
        Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
        _sqsDatabase.CreateMessage(message);
        Entity::SQS::MessageList messageList;
        _sqsDatabase.ReceiveMessages(_region, QUEUE, messageList);

        // act
        Entity::SQS::Message result = messageList[0];
        result = _sqsDatabase.GetMessageByReceiptHandle(result.receiptHandle);

        // assert
        EXPECT_EQ(result.receiptHandle, messageList[0].receiptHandle);
    }

    TEST_F(SQSDatabaseTest, MessageDeleteTest) {

        // arrange
        Entity::SQS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _sqsDatabase.CreateQueue(queue);
        Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
        _sqsDatabase.CreateMessage(message);
        Entity::SQS::MessageList messageList;
        _sqsDatabase.ReceiveMessages(_region, QUEUE, messageList);

        // act
        Entity::SQS::Message resultMessage = messageList[0];
        _sqsDatabase.DeleteMessage(resultMessage);
        long result = _sqsDatabase.CountMessages(_region, QUEUE);

        // assert
        EXPECT_EQ(0, result);
    }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_SQSDATABASETEST_H