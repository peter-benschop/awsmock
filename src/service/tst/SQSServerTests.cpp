//
// Created by vogje01 on 21/10/2023.
//

#ifndef AWMOCK_CORE_SQSSERVERTEST_H
#define AWMOCK_CORE_SQSSERVERTEST_H

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
                                "&Tag.Key=QueueType" \
                                "&Tag.Value=Production"
#define LIST_QUEUE_REQUEST "Action=ListQueues"
#define LIST_QUEUE_RESPONSE "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<ListQueuesResponse>\n\t<ListQueuesResult>\n\t\t<QueueUrl>http://localhost:4566/000000000000/TestQueue</QueueUrl>\n\t</ListQueuesResult>\n\t<ResponseMetadata>\n\t\t<RequestId>b3f94441-5353-406e-85b7-566a12218fdb</RequestId>\n\t</ResponseMetadata>\n</ListQueuesResponse>\n"
#define DELETE_QUEUE_REQUEST "Action=DeleteQueue" \
                             "&QueueUrl=http://localhost:4566/000000000000/TestQueue"

namespace AwsMock::Service {

  class SQSServerTest : public ::testing::Test {

    protected:

      void SetUp() override {

        // Set log level
        Core::LogStream::SetGlobalLevel("error");

        // Create some test objects
        _extraHeaders["Authorization"] =
            "AWS4-HMAC-SHA256 Credential=none/20230618/eu-central-1/sqs/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840";

        // Define endpoint
        std::string _port = _configuration.getString("awsmock.service.sqs.port", std::to_string(SQS_DEFAULT_PORT));
        std::string _host = _configuration.getString("awsmock.service.sqs.host", SQS_DEFAULT_HOST);
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
        //Poco::ThreadPool::defaultPool().stopAll();
      }

      Core::CurlUtils _curlUtils;
      std::string _testFile, _endpoint;
      std::map<std::string, std::string> _extraHeaders;
      Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
      Core::MetricService _metricService = Core::MetricService(_configuration);
      Database::SQSDatabase _database = Database::SQSDatabase(_configuration);
      SQSServer _sqsServer = SQSServer(_configuration, _metricService);
  };

  TEST_F(SQSServerTest, QueueCreateTest) {

    // arrange

    // act
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_EQ(1, queueList.size());
  }

  TEST_F(SQSServerTest, QueueListTest) {

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

  TEST_F(SQSServerTest, QueueDeleteTest) {

    // arrange
    Core::CurlResponse createResponse = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);

    // act
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint, _extraHeaders, DELETE_QUEUE_REQUEST);
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_EQ(0, queueList.size());
  }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_SQSSERVERTEST_H