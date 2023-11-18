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

  class SQSServerCppTest : public ::testing::Test {

  protected:

    void SetUp() override {

      // Set log level
      Core::LogStream::SetGlobalLevel("error");

      // Create some test objects
      _extraHeaders["Authorization"] = Core::AwsUtils::GetAuthorizationHeader(_configuration, "sqs");
      _extraHeaders["User-Agent"] = "aws-sdk-cpp";

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
    Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::SQSDatabase _database = Database::SQSDatabase(_configuration);
    SQSServer _sqsServer = SQSServer(_configuration, _metricService);
  };

  TEST_F(SQSServerCppTest, QueueCreateTest) {

    // arrange

    // act
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_EQ(1, queueList.size());
  }

  TEST_F(SQSServerCppTest, QueueListTest) {

    // arrange
    Core::CurlResponse createResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    EXPECT_TRUE(createResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, LIST_QUEUE_REQUEST);
    EXPECT_TRUE(createResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_TRUE(Core::StringUtils::Contains(response.output, "TestQueue"));
  }

  TEST_F(SQSServerCppTest, QueueDeleteTest) {

    // arrange
    Core::CurlResponse curlResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    Dto::SQS::CreateQueueResponse createResponse;
    createResponse.FromXml(curlResponse.output);

    // act
    std::string deleteQueueRequest = "Action=DeleteQueue&QueueUrl=" + createResponse.queueUrl;
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint, _extraHeaders, deleteQueueRequest);
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_EQ(0, queueList.size());
  }

} // namespace AwsMock::Core

#endif // AWMOCK_SQS_CPP_SERVERTEST_H