//
// Created by vogje01 on 21/10/2023.
//

#ifndef AWMOCK_SQS_JAVA_SERVERTEST_H
#define AWMOCK_SQS_JAVA_SERVERTEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/dto/sqs/CreateQueueResponse.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/SQSServer.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define MESSAGE "{\"test-attribute\":\"test-value\"}"
#define VERSION std::string("2012-11-05")
#define CREATE_QUEUE_REQUEST "{\"QueueName\":\"TestQueue\"}"
#define LIST_QUEUE_REQUEST "Action=ListQueues"
#define GET_QUEUE_URL_REQUEST "{\"QueueName\":\"TestQueue\"}"
#define SEND_MESSAGE_REQUEST "{\"QueueName\":\"TestQueue\", \"MessageBody\":\"testattribute\"}"

namespace AwsMock::Service {

  class SQSServerJsonTest : public ::testing::Test {

  protected:

    void SetUp() override {

      // Set log level
      Core::LogStream::SetGlobalLevel("error");

      // Create some test objects
      _extraHeaders["Authorization"] = Core::AwsUtils::GetAuthorizationHeader(_configuration, "sqs");
      _extraHeaders["Content-Type"] = Core::AwsUtils::GetContentTypeHeader("json");

      // Define endpoint. This is the endpoint of the SQS server, not the gateway
      std::string _port = _configuration.getString("awsmock.module.sqs.port", std::to_string(SQS_DEFAULT_PORT));
      std::string _host = _configuration.getString("awsmock.module.sqs.host", SQS_DEFAULT_HOST);
      _endpoint = "http://" + _host + ":" + _port;

      // Start HTTP manager
      Poco::ThreadPool::defaultPool().start(_sqsServer);
      while (!_sqsServer.IsRunning()) {
        Poco::Thread::sleep(1000);
      }
    }

    void TearDown() override {
      _sqsServer.StopServer();
      _database.DeleteAllQueues();
      Core::FileUtils::DeleteFile(_testFile);
    }

    Core::CurlUtils _curlUtils;
    std::string _testFile, _endpoint;
    std::map<std::string, std::string> _extraHeaders;
    Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration();
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::SQSDatabase _database = Database::SQSDatabase(_configuration);
    SQSServer _sqsServer = SQSServer(_configuration, _metricService);
  };

  TEST_F(SQSServerJsonTest, QueueCreateTest) {

    // arrange

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "create-queue");
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_EQ(1, queueList.size());
  }

  TEST_F(SQSServerJsonTest, QueueListTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "create-queue");
    Core::CurlResponse createResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    EXPECT_TRUE(createResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "list-queues");
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, LIST_QUEUE_REQUEST);
    EXPECT_TRUE(createResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_TRUE(Core::StringUtils::Contains(response.output, "TestQueue"));
  }

  TEST_F(SQSServerJsonTest, QueueDeleteTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "create-queue");
    Core::CurlResponse curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    EXPECT_TRUE(curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Dto::SQS::CreateQueueResponse createResponse;
    createResponse.FromJson(curlResponse.output);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "delete-queue");
    std::string deleteQueueRequest = "{\"QueueUrl\":\"" + createResponse.queueUrl + "\"}";
    curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint, _extraHeaders, deleteQueueRequest);
    EXPECT_TRUE(curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_EQ(0, queueList.size());
  }

  TEST_F(SQSServerJsonTest, QueueGetUrlTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "create-queue");
    Core::CurlResponse curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    EXPECT_TRUE(curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Dto::SQS::CreateQueueResponse createResponse;
    createResponse.FromJson(curlResponse.output);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "get-queue-url");
    curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, GET_QUEUE_URL_REQUEST);
    EXPECT_TRUE(curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Dto::SQS::GetQueueUrlResponse getQueueUrlResponse;
    getQueueUrlResponse.FromJson(curlResponse.output);

    // assert
    EXPECT_TRUE(Core::StringUtils::Contains(getQueueUrlResponse.queueUrl, "TestQueue"));
  }

  TEST_F(SQSServerJsonTest, MessageSendTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "create-queue");
    Core::CurlResponse curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    EXPECT_TRUE(curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Dto::SQS::CreateQueueResponse createResponse;
    createResponse.FromJson(curlResponse.output);

    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "get-queue-url");
    curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, GET_QUEUE_URL_REQUEST);
    EXPECT_TRUE(curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Dto::SQS::GetQueueUrlResponse getQueueUrlResponse;
    getQueueUrlResponse.FromJson(curlResponse.output);
    std::string queueUrl = getQueueUrlResponse.queueUrl;

    // act
    std::string body = "{\"QueueUrl\":\"" + queueUrl + "\", \"MessageBody\":\"test\"}";
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "send-message");
    curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, body);
    EXPECT_TRUE(curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Dto::SQS::SendMessageResponse sendMessageResponse;
    sendMessageResponse.FromJson(curlResponse.output);
    long messageCount = _database.CountMessages(REGION, queueUrl);

    // assert
    EXPECT_FALSE(sendMessageResponse.messageId.empty());
    EXPECT_EQ(1, messageCount);
  }

  TEST_F(SQSServerJsonTest, QueuePurgeTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "create-queue");
    Core::CurlResponse curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    EXPECT_TRUE(curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Dto::SQS::CreateQueueResponse createResponse;
    createResponse.FromJson(curlResponse.output);

    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "get-queue-url");
    curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, GET_QUEUE_URL_REQUEST);
    EXPECT_TRUE(curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Dto::SQS::GetQueueUrlResponse getQueueUrlResponse;
    getQueueUrlResponse.FromJson(curlResponse.output);
    std::string queueUrl = getQueueUrlResponse.queueUrl;

    std::string body = "{\"QueueUrl\":\"" + queueUrl + "\", \"MessageBody\":\"test\"}";
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "send-message");
    curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, body);
    EXPECT_TRUE(curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Dto::SQS::SendMessageResponse sendMessageResponse;
    sendMessageResponse.FromJson(curlResponse.output);

    // act
    body = "{\"QueueUrl\":\"" + queueUrl + "\"}";
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("sqs", "purge-queue");
    _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, body);
    long messageCount = _database.CountMessages(REGION, queueUrl);

    // assert
    EXPECT_EQ(0, messageCount);
  }

} // namespace AwsMock::Core

#endif // AWMOCK_SQS_JAVA_SERVERTEST_H