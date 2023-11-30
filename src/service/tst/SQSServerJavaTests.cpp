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
#include <awsmock/service/SQSService.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define CREATE_QUEUE_REQUEST "Action=CreateQueue" \
                                "&QueueName=TestQueue" \
                                "&Attribute.1.Name=VisibilityTimeout" \
                                "&Attribute.1.Value=40" \
                                "&Tag.1.Key=QueueType" \
                                "&Tag.1.Value=Production"
#define LIST_QUEUE_REQUEST "Action=ListQueues"

namespace AwsMock::Service {

  class SQSServerJavaTest : public ::testing::Test {

  protected:

    void SetUp() override {

      // Set HTTP headers
      _extraHeaders["Authorization"] = Core::AwsUtils::GetAuthorizationHeader(_configuration, "sqs");
      _extraHeaders["Content-Type"] = Core::AwsUtils::GetContentTypeHeader("xml");

      // Define endpoint. This is the endpoint of the SQS server, not the gateway
      std::string _port = _configuration.getString("awsmock.module.sqs.port", std::to_string(SQS_DEFAULT_PORT));
      std::string _host = _configuration.getString("awsmock.module.sqs.host", SQS_DEFAULT_HOST);
      _endpoint = "http://" + _host + ":" + _port;

      // Start HTTP manager
      Poco::ThreadPool::defaultPool().start(_sqsServer);
      while (!_sqsServer.IsRunning()) {
        Poco::Thread::sleep(500);
      }
    }

    void TearDown() override {
      _sqsServer.StopServer();
      _database.DeleteAllQueues();
    }

    Core::CurlUtils _curlUtils;
    std::string _endpoint;
    std::map<std::string, std::string> _extraHeaders;
    Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration();
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::SQSDatabase _database = Database::SQSDatabase(_configuration);
    SQSServer _sqsServer = SQSServer(_configuration, _metricService);
  };

  TEST_F(SQSServerJavaTest, QueueCreateTest) {

    // arrange

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetJava2UserAgentHeader("sqs", "create-queue");
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_EQ(1, queueList.size());
  }

  TEST_F(SQSServerJavaTest, QueueListTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetJava2UserAgentHeader("sqs", "create-queue");
    Core::CurlResponse createResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    EXPECT_TRUE(createResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetJava2UserAgentHeader("sqs", "list-queues");
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, LIST_QUEUE_REQUEST);
    EXPECT_TRUE(createResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_TRUE(Core::StringUtils::Contains(response.output, "TestQueue"));
  }

  TEST_F(SQSServerJavaTest, QueueDeleteTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetJava2UserAgentHeader("sqs", "create-queue");
    Core::CurlResponse curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    Dto::SQS::CreateQueueResponse createResponse;
    createResponse.FromXml(curlResponse.output);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetJava2UserAgentHeader("sqs", "delete-queue");
    std::string deleteQueueRequest = "Action=DeleteQueue&QueueUrl=" + createResponse.queueUrl;
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint, _extraHeaders, deleteQueueRequest);
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_EQ(0, queueList.size());
  }

} // namespace AwsMock::Core

#endif // AWMOCK_SQS_CPP_SERVERTEST_H