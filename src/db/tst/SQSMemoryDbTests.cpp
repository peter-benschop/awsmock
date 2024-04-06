//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_SQSMEMORYDBTEST_H
#define AWMOCK_CORE_SQSMEMORYDBTEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/SQSDatabase.h>

#define BODY "{\"TestObject\": \"TestValue\"}"
#define OWNER "test-owner"
#define QUEUE_NAME "test-queue"
#define DLQ_NAME "test-dlqueue"

namespace AwsMock::Database {

  class SQSMemoryDbTest : public ::testing::Test {

  protected:

    void SetUp() override {
      _queueArn = Core::AwsUtils::CreateSqsQueueArn(_configuration, QUEUE_NAME);
      _queueUrl = Core::AwsUtils::CreateSqsQueueUrl(_configuration, QUEUE_NAME);
      _dlqueueUrl = Core::AwsUtils::CreateSqsQueueUrl(_configuration, DLQ_NAME);
      _dlqueueArn = Core::AwsUtils::CreateSqsQueueArn(_configuration, DLQ_NAME);
      _region = _configuration.getString("awsmock.region");
    }

    void TearDown() override {
      _sqsDatabase.DeleteAllQueues();
      _sqsDatabase.DeleteAllMessages();
    }

    std::string _region, _queueUrl, _queueArn, _dlqueueUrl, _dlqueueArn;
    Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration(false);
    SQSDatabase& _sqsDatabase = SQSDatabase::instance();
  };

  TEST_F(SQSMemoryDbTest, QueueCreateTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl, .queueArn=_queueArn};

    // act
    Entity::SQS::Queue result = _sqsDatabase.CreateQueue(queue);

    // assert
    EXPECT_TRUE(result.name == QUEUE_NAME);
    EXPECT_TRUE(result.region == _region);
  }

  TEST_F(SQSMemoryDbTest, QueueUrlExistsTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl, .queueArn=_queueArn};
    _sqsDatabase.CreateQueue(queue);

    // act
    bool result = _sqsDatabase.QueueUrlExists(_region, _queueUrl);

    // assert
    EXPECT_TRUE(result);
  }

  TEST_F(SQSMemoryDbTest, QueueArnExistsTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl, .queueArn=_queueArn};
    _sqsDatabase.CreateQueue(queue);

    // act
    bool result = _sqsDatabase.QueueArnExists(_queueArn);

    // assert
    EXPECT_TRUE(result);
  }

  TEST_F(SQSMemoryDbTest, QueueByIdTest) {

    // arrange
    Entity::SQS::Queue queue = _sqsDatabase.CreateQueue({.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl, .queueArn=_queueArn});

    // act
    Entity::SQS::Queue result = _sqsDatabase.GetQueueById(queue.oid);

    // assert
    EXPECT_TRUE(result.name == QUEUE_NAME);
    EXPECT_TRUE(result.region == _region);
  }

  TEST_F(SQSMemoryDbTest, QueueByArnTest) {

    // arrange
    Entity::SQS::Queue queue = _sqsDatabase.CreateQueue({.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl, .queueArn=_queueArn});

    // act
    Entity::SQS::Queue result = _sqsDatabase.GetQueueByArn(queue.queueArn);

    // assert
    EXPECT_TRUE(result.name == QUEUE_NAME);
    EXPECT_TRUE(result.region == _region);
  }

  TEST_F(SQSMemoryDbTest, QueueByUrlTest) {

    // arrange
    Entity::SQS::Queue queue = _sqsDatabase.CreateQueue({.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl, .queueArn=_queueArn});

    // act
    Entity::SQS::Queue result = _sqsDatabase.GetQueueByUrl(_region, _queueUrl);

    // assert
    EXPECT_TRUE(result.name == QUEUE_NAME);
    EXPECT_TRUE(result.region == _region);
  }

  TEST_F(SQSMemoryDbTest, QueueListTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);

    // act
    Entity::SQS::QueueList result = _sqsDatabase.ListQueues(queue.region);

    // assert
    EXPECT_EQ(result.size(), 1);
  }

  TEST_F(SQSMemoryDbTest, QueuePurgeTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.queueUrl, .body=BODY};
    _sqsDatabase.CreateMessage(message);

    // act
    _sqsDatabase.PurgeQueue(queue.region, queue.queueUrl);
    long result = _sqsDatabase.CountMessages(queue.region, queue.queueUrl);

    // assert
    EXPECT_EQ(0, result);
  }

  TEST_F(SQSMemoryDbTest, QueueUpdateTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);

    // act
    queue.owner = "root";
    Entity::SQS::Queue result = _sqsDatabase.UpdateQueue(queue);

    // assert
    EXPECT_TRUE(result.oid == queue.oid);
    EXPECT_TRUE(result.owner == queue.owner);
  }

  TEST_F(SQSMemoryDbTest, QueueCountTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    _sqsDatabase.CreateQueue(queue);

    // act
    long result = _sqsDatabase.CountQueues(_region);

    // assert
    EXPECT_EQ(1, result);
  }

  TEST_F(SQSMemoryDbTest, QueueCountTotalTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    _sqsDatabase.CreateQueue(queue);

    // act
    long result = _sqsDatabase.CountQueues();

    // assert
    EXPECT_EQ(1, result);
  }

  TEST_F(SQSMemoryDbTest, QueueDeleteTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);

    // act
    _sqsDatabase.DeleteQueue(queue);
    bool result = _sqsDatabase.QueueExists(queue.region, queue.queueUrl);

    // assert
    EXPECT_FALSE(result);
  }

  TEST_F(SQSMemoryDbTest, MessageCreateTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};

    // act
    Entity::SQS::Message result = _sqsDatabase.CreateMessage(message);

    // assert
    EXPECT_FALSE(result.oid.empty());
    EXPECT_TRUE(result.body == BODY);
  }

  TEST_F(SQSMemoryDbTest, MessageExistsTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY, .receiptHandle="10bdf54e6f7"};
    message = _sqsDatabase.CreateMessage(message);

    // act
    bool result = _sqsDatabase.MessageExists(message.receiptHandle);

    // assert
    EXPECT_TRUE(result);
  }

  TEST_F(SQSMemoryDbTest, MessageGetByIdTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.queueUrl, .body=BODY};
    message = _sqsDatabase.CreateMessage(message);

    // act
    Entity::SQS::Message result = _sqsDatabase.GetMessageById(message.oid);

    // assert
    EXPECT_TRUE(message.oid == result.oid);
  }

  TEST_F(SQSMemoryDbTest, MessageReceiveTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
    _sqsDatabase.CreateMessage(message);

    // act
    Entity::SQS::MessageList messageList;
    _sqsDatabase.ReceiveMessages(_region, QUEUE_NAME, 30, 3, messageList);

    // assert
    EXPECT_FALSE(messageList.empty());
  }

  TEST_F(SQSMemoryDbTest, MessageCountTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
    _sqsDatabase.CreateMessage(message);

    // act
    long result = _sqsDatabase.CountMessages(_region, QUEUE_NAME);

    // assert
    EXPECT_EQ(1, result);
  }

  TEST_F(SQSMemoryDbTest, MessageCountStatusTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
    _sqsDatabase.CreateMessage(message);

    // act
    long result = _sqsDatabase.CountMessagesByStatus(_region, QUEUE_NAME, Entity::SQS::MessageStatus::INITIAL);

    // assert
    EXPECT_EQ(1, result);
  }

  TEST_F(SQSMemoryDbTest, MessageResetTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.queueUrl, .body=BODY};
    _sqsDatabase.CreateMessage(message);
    Entity::SQS::MessageList messageList;
    _sqsDatabase.ReceiveMessages(_region, _queueUrl, 1, 3, messageList);
    Poco::Thread().sleep(2000);
    _sqsDatabase.ResetMessages(_queueUrl, 1);

    // act
    _sqsDatabase.ResetMessages(_queueUrl, 1);
    long result = _sqsDatabase.CountMessagesByStatus(_region, _queueUrl, Entity::SQS::MessageStatus::INITIAL);

    // assert
    EXPECT_EQ(1, result);
  }

  TEST_F(SQSMemoryDbTest, MessageDelayTest) {

    // arrange
    Entity::SQS::QueueAttribute queueAttribute;
    queueAttribute.delaySeconds = 1;
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl, .attributes=queueAttribute};
    queue = _sqsDatabase.CreateQueue(queue);

    Poco::DateTime reset;
    reset += Poco::Timespan(queueAttribute.delaySeconds, 0);
    Entity::SQS::Message message = {.region=_region, .queueUrl=_queueUrl, .body=BODY, .status=Entity::SQS::MessageStatus::DELAYED, .reset=reset};
    _sqsDatabase.CreateMessage(message);

    Entity::SQS::MessageList messageList;
    _sqsDatabase.ReceiveMessages(_region, QUEUE_NAME, 1, 3, messageList);
    EXPECT_EQ(0, messageList.size());
    Poco::Thread().sleep(2000);

    // act
    _sqsDatabase.ResetDelayedMessages(_queueUrl, queueAttribute.delaySeconds);
    long result = _sqsDatabase.CountMessagesByStatus(_region, _queueUrl, Entity::SQS::MessageStatus::INITIAL);

    // assert
    EXPECT_EQ(1, result);
  }

  TEST_F(SQSMemoryDbTest, MessageGetByReceiptHandleTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.name, .body=BODY};
    _sqsDatabase.CreateMessage(message);
    Entity::SQS::MessageList messageList;
    _sqsDatabase.ReceiveMessages(_region, QUEUE_NAME, 30, 3, messageList);

    // act
    Entity::SQS::Message result = messageList[0];
    result = _sqsDatabase.GetMessageByReceiptHandle(result.receiptHandle);

    // assert
    EXPECT_EQ(result.receiptHandle, messageList[0].receiptHandle);
  }

  TEST_F(SQSMemoryDbTest, MessageUpdateTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.queueUrl, .body=BODY, .receiptHandle=Core::AwsUtils::CreateSqsReceiptHandler()};
    message = _sqsDatabase.CreateMessage(message);

    // act
    message.status = Entity::SQS::MessageStatus::DELAYED;
    Entity::SQS::Message result = _sqsDatabase.UpdateMessage(message);

    // assert
    EXPECT_TRUE(result.oid == message.oid);
    EXPECT_TRUE(result.status == Entity::SQS::MessageStatus::DELAYED);
  }

  TEST_F(SQSMemoryDbTest, MessageRedriveTest) {

    // arrange
    Entity::SQS::RedrivePolicy redrivePolicy = {.deadLetterTargetArn=_dlqueueArn, .maxReceiveCount=1};
    Entity::SQS::QueueAttribute attribute = {.visibilityTimeout=1, .redrivePolicy=redrivePolicy};

    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl, .attributes=attribute};
    queue = _sqsDatabase.CreateQueue(queue);

    Entity::SQS::Queue dlQueue = {.region=_region, .name=DLQ_NAME, .owner=OWNER, .queueUrl=_dlqueueUrl, .queueArn=_dlqueueArn};
    dlQueue = _sqsDatabase.CreateQueue(dlQueue);

    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.queueUrl, .body=BODY};
    _sqsDatabase.CreateMessage(message);

    // act
    Entity::SQS::MessageList messageList;
    _sqsDatabase.ReceiveMessages(_region, _queueUrl, 1, 3, messageList);
    Poco::Thread::sleep(2000);
    _sqsDatabase.ResetMessages(_queueUrl, 1);
    _sqsDatabase.ReceiveMessages(_region, _queueUrl, 1, 3, messageList);
    Poco::Thread::sleep(2000);
    _sqsDatabase.ResetMessages(_queueUrl, 1);

    _sqsDatabase.RedriveMessages(_queueUrl, redrivePolicy);
    long queueResult = _sqsDatabase.CountMessages(_region, queue.queueUrl);
    long dlqResult = _sqsDatabase.CountMessages(_region, dlQueue.queueUrl);

    // assert
    EXPECT_EQ(0, queueResult);
    EXPECT_EQ(1, dlqResult);
  }

  TEST_F(SQSMemoryDbTest, MessageDeleteTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=queue.queueUrl, .body=BODY};
    _sqsDatabase.CreateMessage(message);
    Entity::SQS::MessageList messageList;
    _sqsDatabase.ReceiveMessages(_region, queue.queueUrl, 30, 3, messageList);

    // act
    Entity::SQS::Message resultMessage = messageList[0];
    _sqsDatabase.DeleteMessage(resultMessage);
    long result = _sqsDatabase.CountMessages(_region, QUEUE_NAME);

    // assert
    EXPECT_EQ(0, result);
  }

  TEST_F(SQSMemoryDbTest, MessageDeleteQueueTest) {

    // arrange
    Entity::SQS::Queue queue = {.region=_region, .name=QUEUE_NAME, .owner=OWNER, .queueUrl=_queueUrl};
    queue = _sqsDatabase.CreateQueue(queue);
    Entity::SQS::Message message = {.region=_region, .queueUrl=_queueUrl, .body=BODY};
    _sqsDatabase.CreateMessage(message);

    // act
    _sqsDatabase.DeleteMessages(_queueUrl);
    long result = _sqsDatabase.CountMessages(_region, QUEUE_NAME);

    // assert
    EXPECT_EQ(0, result);
  }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_SQSMEMORYDBTEST_H