//
// Created by vogje01 on 21/10/2023.
//

#ifndef AWMOCK_SQS_CPP_SERVERTEST_H
#define AWMOCK_SQS_CPP_SERVERTEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/SQSServer.h>

// Test includes
#include <awsmock/core/TestUtils.h>

namespace AwsMock::Service {

  /**
   * Tests the aws-sdk-java interface to the AwsMock system.
   *
   * <p>The aws-mock-java-test.jar file should be installed in <pre>/usr/local/lib</pre>.</p>
   *
   */
  class SQSServerJavaTest : public ::testing::Test {

    protected:

      void SetUp() override {

        // General configuration
        _region = _configuration.getString("awsmock.region", "eu-central-1");

        // Define endpoint. This is the endpoint of the SQS server, not the gateway
        std::string _port = _configuration.getString("awsmock.service.sqs.port", std::to_string(SQS_DEFAULT_PORT));
        std::string _host = _configuration.getString("awsmock.service.sqs.host", SQS_DEFAULT_HOST);
        _configuration.setString("awsmock.service.gateway.port", _port);
        _endpoint = "http://" + _host + ":" + _port;

        // Set base command
        _baseCommand = "java -jar /usr/local/lib/awsmock-java-test-0.0.1-SNAPSHOT-jar-with-dependencies.jar " + _endpoint;

        // Start HTTP manager
        Poco::ThreadPool::defaultPool().start(_sqsServer);
      }

      void TearDown() override {
        _database.DeleteAllMessages();
        _database.DeleteAllQueues();
        _sqsServer.StopServer();
      }

      Core::CurlUtils _curlUtils;
      std::string _endpoint, _baseCommand, _region;
      std::map<std::string, std::string> _extraHeaders;
      Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration(false);
      Core::MetricService _metricService = Core::MetricService(_configuration);
      Database::SQSDatabase _database = Database::SQSDatabase(_configuration);
      SQSServer _sqsServer = SQSServer(_configuration, _metricService);
  };

  TEST_F(SQSServerJavaTest, QueueCreateTest) {

    // arrange

    // act
    Core::ExecResult result = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_TRUE(result.status == 0);
    EXPECT_EQ(1, queueList.size());
  }

  TEST_F(SQSServerJavaTest, QueueListTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult listResult = Core::SystemUtils::Exec(_baseCommand + " sqs list-queues");

    // assert
    EXPECT_EQ(0, listResult.status);
    EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, "test-queue"));
  }

  TEST_F(SQSServerJavaTest, QueuePurgeTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
    EXPECT_EQ(0, getQueueUrlResult.status);
    std::string queueUrl = getQueueUrlResult.output;
    Core::ExecResult sendResult = Core::SystemUtils::Exec(_baseCommand + " sqs send-message " + queueUrl + " test-message");
    EXPECT_EQ(0, sendResult.status);

    // act
    Core::ExecResult purgeResult = Core::SystemUtils::Exec(_baseCommand + " sqs purge-queue " + queueUrl);
    long messageCount = _database.CountMessages();

    // assert
    EXPECT_EQ(0, purgeResult.status);
    EXPECT_EQ(0, messageCount);
  }

  TEST_F(SQSServerJavaTest, QueueGetAllAttributeTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
    EXPECT_EQ(0, getQueueUrlResult.status);
    std::string queueUrl = getQueueUrlResult.output;
    Core::ExecResult sendResult = Core::SystemUtils::Exec(_baseCommand + " sqs send-message " + queueUrl + " test-message");
    EXPECT_EQ(0, sendResult.status);

    // act
    Core::ExecResult getQueueAttributeResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-attributes " + queueUrl + " All");

    // assert
    EXPECT_EQ(0, getQueueAttributeResult.status);
    EXPECT_TRUE(Core::StringUtils::Contains(getQueueAttributeResult.output, "CreatedTimestamp"));
  }

  TEST_F(SQSServerJavaTest, QueueGetSomeAttributeTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
    EXPECT_EQ(0, getQueueUrlResult.status);
    std::string queueUrl = getQueueUrlResult.output;
    Core::ExecResult sendResult = Core::SystemUtils::Exec(_baseCommand + " sqs send-message " + queueUrl + " test-message");
    EXPECT_EQ(0, sendResult.status);

    // act
    Core::ExecResult getQueueAttributeResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-attributes " + queueUrl + " ReceiveMessageWaitTimeSeconds");

    // assert
    EXPECT_EQ(0, getQueueAttributeResult.status);
    EXPECT_TRUE(Core::StringUtils::Contains(getQueueAttributeResult.output, "ReceiveMessageWaitTimeSeconds"));
  }

  TEST_F(SQSServerJavaTest, QueueSetAttributeTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
    EXPECT_EQ(0, getQueueUrlResult.status);
    std::string queueUrl = getQueueUrlResult.output;
    Core::ExecResult sendResult = Core::SystemUtils::Exec(_baseCommand + " sqs send-message " + queueUrl + " test-message");
    EXPECT_EQ(0, sendResult.status);

    // act
    Core::ExecResult setQueueAttributeResult = Core::SystemUtils::Exec(_baseCommand + " sqs set-queue-userAttributes " + queueUrl + " VisibilityTimeout=42");

    // assert
    EXPECT_EQ(0, setQueueAttributeResult.status);
  }

  TEST_F(SQSServerJavaTest, QueueGetUrlTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
    EXPECT_EQ(0, getQueueUrlResult.status);
    std::string queueUrl = getQueueUrlResult.output;

    // assert
    EXPECT_EQ(0, getQueueUrlResult.status);
    EXPECT_TRUE(queueUrl == _endpoint + "/000000000000/test-queue");
  }

  TEST_F(SQSServerJavaTest, QueueDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
    EXPECT_EQ(0, getQueueUrlResult.status);
    std::string queueUrl = getQueueUrlResult.output;

    // act
    Core::ExecResult deleteResult = Core::SystemUtils::Exec(_baseCommand + " sqs delete-queue " + queueUrl);
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_EQ(0, deleteResult.status);
    EXPECT_EQ(0, queueList.size());
  }

  TEST_F(SQSServerJavaTest, MessageSendTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
    EXPECT_EQ(0, getQueueUrlResult.status);
    std::string queueUrl = getQueueUrlResult.output;

    // act
    Core::ExecResult sendResult = Core::SystemUtils::Exec(_baseCommand + " sqs send-message " + queueUrl + " test-message");
    long messageCount = _database.CountMessages();

    // assert
    EXPECT_EQ(0, sendResult.status);
    EXPECT_EQ(1, messageCount);
  }

  TEST_F(SQSServerJavaTest, MessageReceiveTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
    EXPECT_EQ(0, getQueueUrlResult.status);
    std::string queueUrl = getQueueUrlResult.output;
    Core::ExecResult sendResult = Core::SystemUtils::Exec(_baseCommand + " sqs send-message " + queueUrl + " \"test-message\"");
    EXPECT_EQ(0, sendResult.status);

    // act
    Core::ExecResult receiveResult = Core::SystemUtils::Exec(_baseCommand + " sqs receive-message " + queueUrl + " 1 5 5");
    long messageCount = _database.CountMessages();

    // assert
    EXPECT_EQ(0, receiveResult.status);
    EXPECT_EQ(1, messageCount);
  }

  TEST_F(SQSServerJavaTest, MessageChangeVisibilityTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
    EXPECT_EQ(0, getQueueUrlResult.status);
    std::string queueUrl = getQueueUrlResult.output;
    Core::ExecResult sendResult = Core::SystemUtils::Exec(_baseCommand + " sqs send-message " + queueUrl + " test-message");
    EXPECT_EQ(0, sendResult.status);
    Core::ExecResult receiveResult = Core::SystemUtils::Exec(_baseCommand + " sqs receive-message " + queueUrl + " 1 5 5");
    EXPECT_EQ(0, receiveResult.status);
    std::string receiptHandle = receiveResult.output;

    // act
    Core::ExecResult changeVisibilityResult = Core::SystemUtils::Exec(_baseCommand + " sqs change-visibility-timeout " + queueUrl + " " + receiptHandle + " 42");

    // assert
    EXPECT_EQ(0, changeVisibilityResult.status);
  }

  TEST_F(SQSServerJavaTest, MessageDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
    EXPECT_EQ(0, getQueueUrlResult.status);
    std::string queueUrl = getQueueUrlResult.output;
    Core::ExecResult sendResult = Core::SystemUtils::Exec(_baseCommand + " sqs send-message " + queueUrl + " \"test-message\"");
    EXPECT_EQ(0, sendResult.status);
    Core::ExecResult receiveResult = Core::SystemUtils::Exec(_baseCommand + " sqs receive-message " + queueUrl + " 1 5 5");
    EXPECT_EQ(0, receiveResult.status);
    std::string receiptHandle = receiveResult.output;

    // act
    Core::ExecResult deleteResult = Core::SystemUtils::Exec(_baseCommand + " sqs delete-message " + queueUrl + " " + receiptHandle);
    long messageCount = _database.CountMessages();

    // assert
    EXPECT_EQ(0, receiveResult.status);
    EXPECT_EQ(0, messageCount);
  }

} // namespace AwsMock::Core

#endif // AWMOCK_SQS_CPP_SERVERTEST_H