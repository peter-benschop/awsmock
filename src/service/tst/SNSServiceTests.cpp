//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_SERVICE_SNS_SERVICE_TEST_H
#define AWMOCK_SERVICE_SNS_SERVICE_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/SNSService.h>
#include <awsmock/service/SQSService.h>

// AwsMOck includes
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define TOPIC "test-topic"
#define QUEUE "test-queue"
#define QUEUE_URL "http://localhost:4566/000000000000/test-queue"
#define BODY "{\"TestObject\": \"TestValue\"}"
#define BODY_MD5 "bf54bf4281dc11635fcdd2d7d6c9e126"
#define OWNER "test-owner"

namespace AwsMock::Service {

  class SNSServiceTest : public ::testing::Test {

    protected:

      void SetUp() override {
        // Set log level
        Core::LogStream::SetGlobalLevel("error");
      }

      void TearDown() override {
        _snsDatabase.DeleteAllMessages();
        _snsDatabase.DeleteAllTopics();
        _sqsDatabase.DeleteAllMessages();
        _sqsDatabase.DeleteAllQueues();
      }

      Poco::Condition _condition;
      Core::Configuration& _configuration = Core::TestUtils::GetTestConfiguration(false);
      Database::SNSDatabase& _snsDatabase = Database::SNSDatabase::instance();
      Database::SQSDatabase& _sqsDatabase = Database::SQSDatabase::instance();
      SNSService _snsService = SNSService(_configuration, _condition);
      SQSService _sqsService = SQSService(_configuration, _condition);
  };

  TEST_F(SNSServiceTest, TopicCreateTest) {

    // arrange
    Dto::SNS::CreateTopicRequest request = {.region=REGION, .topicName=TOPIC, .owner=OWNER};

    // act
    Dto::SNS::CreateTopicResponse response = _snsService.CreateTopic(request);

    // assert
    EXPECT_TRUE(response.region == REGION);
    EXPECT_TRUE(response.name == TOPIC);
  }

  TEST_F(SNSServiceTest, TopicDeleteTest) {

    // arrange
    Dto::SNS::CreateTopicRequest topicRequest = {.region=REGION, .topicName=TOPIC, .owner=OWNER};
    Dto::SNS::CreateTopicResponse topicResponse = _snsService.CreateTopic(topicRequest);

    // act
    EXPECT_NO_THROW({ _snsService.DeleteTopic(topicResponse.region, topicResponse.topicArn); });

    // assert
    EXPECT_EQ(0, _snsDatabase.ListTopics(REGION).size());
  }

  TEST_F(SNSServiceTest, SubscribeTest) {

    // arrange
    Dto::SNS::CreateTopicRequest topicRequest = {.region=REGION, .topicName=TOPIC, .owner=OWNER};
    Dto::SNS::CreateTopicResponse topicResponse = _snsService.CreateTopic(topicRequest);
    Dto::SQS::CreateQueueRequest queueRequest = {.queueName=QUEUE, .queueUrl=QUEUE_URL, .owner=OWNER};
    queueRequest.region = REGION;
    queueRequest.requestId = Poco::UUIDGenerator().createRandom().toString();
    Dto::SQS::CreateQueueResponse queueResponse = _sqsService.CreateQueue(queueRequest);

    // act
    Dto::SNS::SubscribeRequest subscribeRequest = {.region=REGION, .topicArn=topicResponse.topicArn, .protocol="sqs", .endpoint=queueResponse.queueArn, .owner=OWNER};
    Dto::SNS::SubscribeResponse subscribeResponse = _snsService.Subscribe(subscribeRequest);
    Dto::SNS::ListTopicsResponse response = _snsService.ListTopics(REGION);

    // assert
    EXPECT_FALSE(subscribeResponse.subscriptionArn.empty());
    EXPECT_EQ(1, response.topicList[0].subscriptions.size());
  }

  TEST_F(SNSServiceTest, UnsubscribeTest) {

    // arrange
    Dto::SNS::CreateTopicRequest topicRequest = {.region=REGION, .topicName=TOPIC, .owner=OWNER};
    Dto::SNS::CreateTopicResponse topicResponse = _snsService.CreateTopic(topicRequest);
    Dto::SQS::CreateQueueRequest queueRequest = {.queueName=QUEUE, .queueUrl=QUEUE_URL, .owner=OWNER};
    queueRequest.region = REGION;
    queueRequest.requestId = Poco::UUIDGenerator().createRandom().toString();

    Dto::SQS::CreateQueueResponse queueResponse = _sqsService.CreateQueue(queueRequest);
    Dto::SNS::SubscribeRequest subscribeRequest = {.region=REGION, .topicArn=topicResponse.topicArn, .protocol="sqs", .endpoint=queueResponse.queueArn, .owner=OWNER};
    Dto::SNS::SubscribeResponse subscribeResponse = _snsService.Subscribe(subscribeRequest);

    // act
    Dto::SNS::UnsubscribeRequest unsubscribeRequest = {.region=REGION, .subscriptionArn=subscribeResponse.subscriptionArn};
    Dto::SNS::UnsubscribeResponse unsubscribeResponse = _snsService.Unsubscribe(unsubscribeRequest);
    Dto::SNS::ListTopicsResponse response = _snsService.ListTopics(REGION);

    // assert
    EXPECT_FALSE(subscribeResponse.subscriptionArn.empty());
    EXPECT_EQ(0, response.topicList[0].subscriptions.size());
  }

  TEST_F(SNSServiceTest, PublishMessageTest) {

    // arrange
    Dto::SNS::CreateTopicRequest topicRequest = {.region=REGION, .topicName=TOPIC, .owner=OWNER};
    Dto::SNS::CreateTopicResponse topicResponse = _snsService.CreateTopic(topicRequest);
    Dto::SNS::PublishRequest request = {.region=REGION, .topicArn=topicResponse.topicArn, .message=BODY};

    // act
    Dto::SNS::PublishResponse response = _snsService.Publish(request);

    // assert
    EXPECT_FALSE(response.messageId.empty());
    EXPECT_FALSE(response.ToXml().empty());
  }

  TEST_F(SNSServiceTest, MessageReceiveTest) {

    // arrange
    Dto::SNS::CreateTopicRequest topicRequest = {.region=REGION, .topicName=TOPIC, .owner=OWNER};
    Dto::SNS::CreateTopicResponse topicResponse = _snsService.CreateTopic(topicRequest);
    Dto::SQS::CreateQueueRequest queueRequest = {.queueName=QUEUE, .queueUrl=QUEUE_URL, .owner=OWNER};
    queueRequest.region = REGION;
    queueRequest.requestId = Poco::UUIDGenerator().createRandom().toString();
    Dto::SQS::CreateQueueResponse queueResponse = _sqsService.CreateQueue(queueRequest);
    Dto::SNS::SubscribeRequest subscribeRequest = {.region=REGION, .topicArn=topicResponse.topicArn, .protocol="sqs", .endpoint=queueResponse.queueArn, .owner=OWNER};
    Dto::SNS::SubscribeResponse subscribeResponse = _snsService.Subscribe(subscribeRequest);
    Dto::SNS::PublishRequest request = {.region=REGION, .topicArn=topicResponse.topicArn, .message=BODY};
    Dto::SNS::PublishResponse response = _snsService.Publish(request);

    // act
    Dto::SQS::ReceiveMessageRequest receiveRequest = {.region=REGION, .queueUrl=QUEUE_URL, .queueName=QUEUE, .maxMessages=10, .waitTimeSeconds=5};
    Dto::SQS::ReceiveMessageResponse receiveResponse = _sqsService.ReceiveMessages(receiveRequest);

    // assert
    EXPECT_EQ(receiveResponse.messageList.size(), 1);
  }

} // namespace AwsMock::Core

#endif // AWMOCK_SERVICE_SNS_SERVICE_TEST_H