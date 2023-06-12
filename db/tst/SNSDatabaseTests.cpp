//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_SNSDATABASETEST_H
#define AWMOCK_CORE_SNSDATABASETEST_H

// GTest includes
#include <gtest/gtest.h>

// Poco includes
#include "Poco/Path.h"

// Local includes
#include <awsmock/core/Configuration.h>
#include <awsmock/db/SNSDatabase.h>

#define CONFIG_FILE "/tmp/aws-mock.properties"
#define REGION "eu-central-1"
#define TOPIC "test-topic"
#define TOPIC_ARN "arn:aws:sns:eu-central-1:000000000000:test-topic"
#define TOPIC_URL "http://localhost:4567/000000000000/test-topic"
#define BODY "{\"TestObject\": \"TestValue\"}"
#define OWNER "test-owner"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    class SNSDatabaseTest : public ::testing::Test {

    protected:

      void SetUp() override {
          _region = _configuration.getString("awsmock.region");
      }

      void TearDown() override {
          _snsDatabase.DeleteAllTopics();
          //_snsDatabase.DeleteAllMessages();
      }

      std::string _region;
      Core::Configuration _configuration = Core::Configuration(CONFIG_FILE);
      SNSDatabase _snsDatabase = SNSDatabase(_configuration);
    };

    TEST_F(SNSDatabaseTest, TopicCreateTest) {

        // arrange
        Entity::SNS::Topic topic = {.region=_region, .topicName=TOPIC, .owner=OWNER};

        // act
        Entity::SNS::Topic result = _snsDatabase.CreateTopic(topic);

        // assert
        EXPECT_TRUE(result.topicName == TOPIC);
        EXPECT_TRUE(result.region == REGION);
        EXPECT_FALSE(result.oid.empty());
    }

    TEST_F(SNSDatabaseTest, TopicListTest) {

        // arrange
        Entity::SNS::Topic topic = _snsDatabase.CreateTopic({.region=_region, .topicName=TOPIC, .owner=OWNER});

        // act
        Entity::SNS::TopicList result = _snsDatabase.ListTopics(topic.region);

        // assert
        EXPECT_EQ(result.size(), 1);
    }

    /*TEST_F(SNSDatabaseTest, QueuePurgeTest) {

        // arrange
        Entity::SNS::Queue queue = {.region=_region, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _snsDatabase.CreateQueue(queue);
        Entity::SNS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
        _snsDatabase.CreateMessage(message);

        // act
        _snsDatabase.PurgeQueue(queue.region, queue.queueUrl);
        long result = _snsDatabase.CountMessages(queue.region, queue.queueUrl);

        // assert
        EXPECT_EQ(0, result);
    }*/

    TEST_F(SNSDatabaseTest, TopicDeleteTest) {

        // arrange
        Entity::SNS::Topic topic = _snsDatabase.CreateTopic({.region=_region, .topicName=TOPIC, .owner=OWNER, .topicArn=TOPIC_ARN});

        // act
        _snsDatabase.DeleteTopic(topic);
        bool result = _snsDatabase.TopicExists(topic.region, topic.topicName);

        // assert
        EXPECT_FALSE(result);
    }

    TEST_F(SNSDatabaseTest, MessageCreateTest) {

        // arrange
        Entity::SNS::Topic topic = {.region=_region, .topicName=TOPIC, .owner=OWNER, .topicArn=TOPIC_ARN};
        topic = _snsDatabase.CreateTopic(topic);
        Entity::SNS::Message message = {.region=_region, .topicArn=topic.topicArn, .message=BODY};

        // act
        Entity::SNS::Message result = _snsDatabase.CreateMessage(message);

        // assert
        EXPECT_FALSE(result.oid.empty());
        EXPECT_TRUE(result.message == BODY);
    }

    /*TEST_F(SNSDatabaseTest, MessageReceiveTest) {

        // arrange
        Entity::SNS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _snsDatabase.CreateQueue(queue);
        Entity::SNS::Message message = {.region=REGION, .queueUrl=queue.name, .body=BODY};
        _snsDatabase.CreateMessage(message);

        // act
        Entity::SNS::MessageList messageList;
        _snsDatabase.ReceiveMessages(REGION, QUEUE, messageList);

        // assert
        EXPECT_FALSE(messageList.empty());
    }

    TEST_F(SNSDatabaseTest, MessageCountTest) {

        // arrange
        Entity::SNS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _snsDatabase.CreateQueue(queue);
        Entity::SNS::Message message = {.region=REGION, .queueUrl=queue.name, .body=BODY};
        _snsDatabase.CreateMessage(message);

        // act
        long result = _snsDatabase.CountMessages(REGION, QUEUE);

        // assert
        EXPECT_EQ(1, result);
    }

    TEST_F(SNSDatabaseTest, MessageCountStatusTest) {

        // arrange
        Entity::SNS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _snsDatabase.CreateQueue(queue);
        Entity::SNS::Message message = {.region=REGION, .queueUrl=queue.name, .body=BODY};
        _snsDatabase.CreateMessage(message);

        // act
        long result = _snsDatabase.CountMessagesByStatus(REGION, QUEUE, Entity::SNS::INITIAL);

        // assert
        EXPECT_EQ(1, result);
    }

    TEST_F(SNSDatabaseTest, MessageResetTest) {

        // arrange
        Entity::SNS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _snsDatabase.CreateQueue(queue);
        Entity::SNS::Message message = {.region=REGION, .queueUrl=queue.name, .body=BODY};
        _snsDatabase.CreateMessage(message);
        Entity::SNS::MessageList messageList;
        _snsDatabase.ReceiveMessages(REGION, QUEUE, messageList);
        Poco::Thread().sleep(1000);

        // act
        _snsDatabase.ResetMessages(QUEUE, 1);
        long result = _snsDatabase.CountMessagesByStatus(REGION, QUEUE, Entity::SNS::INITIAL);

        // assert
        EXPECT_EQ(1, result);
    }

    TEST_F(SNSDatabaseTest, MessageGetByReceiptHandleTest) {

        // arrange
        Entity::SNS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _snsDatabase.CreateQueue(queue);
        Entity::SNS::Message message = {.region=REGION, .queueUrl=queue.name, .body=BODY};
        _snsDatabase.CreateMessage(message);
        Entity::SNS::MessageList messageList;
        _snsDatabase.ReceiveMessages(REGION, QUEUE, messageList);

        // act
        Entity::SNS::Message result = messageList[0];
        result = _snsDatabase.GetMessageByReceiptHandle(result.receiptHandle);

        // assert
        EXPECT_EQ(result.receiptHandle, messageList[0].receiptHandle);
    }

    TEST_F(SNSDatabaseTest, MessageDeleteTest) {

        // arrange
        Entity::SNS::Queue queue = {.region=REGION, .name=QUEUE, .owner=OWNER, .queueUrl=QUEUE_URL};
        queue = _snsDatabase.CreateQueue(queue);
        Entity::SNS::Message message = {.region=REGION, .queueUrl=queue.name, .body=BODY};
        _snsDatabase.CreateMessage(message);
        Entity::SNS::MessageList messageList;
        _snsDatabase.ReceiveMessages(REGION, QUEUE, messageList);

        // act
        Entity::SNS::Message resultMessage = messageList[0];
        _snsDatabase.DeleteMessage(resultMessage);
        long result = _snsDatabase.CountMessages(REGION, QUEUE);

        // assert
        EXPECT_EQ(0, result);
    }*/

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_SNSDATABASETEST_H