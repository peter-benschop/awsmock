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
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/SQSServer.h>
#include <awsmock/service/SQSService.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
// =============================================== Body ===============================================================
// Action=CreateQueue&Version=2012-11-05&QueueName=test-queue&Attribute.1.Name=VisibilityTimeout&Attribute.1.Value=99
// ====================================================================================================================
// ============================================== Headers =============================================================
// Host: 192.168.178.34:4566
// amz-sdk-invocation-id: f3f02263-3145-09b3-7421-915c0582fe4a
// amz-sdk-request: attempt=1; max=3
// Authorization: AWS4-HMAC-SHA256 Credential=ASIATJV5PDKHUCV346GW/20231117/eu-central-1/sqs/aws4_request, SignedHeaders=amz-sdk-invocation-id;amz-sdk-request;content-length;content-type;host;x-amz-date;x-amz-security-token, Signature=940ebc3db38c6706d5655dd73c1f5af71d63441a662430113bc6a8fcb0442f7c
// Content-Type: application/x-www-form-urlencoded; charset=utf-8
// User-Agent: aws-sdk-java/2.20.63 Linux/6.1.0-13-amd64 OpenJDK_64-Bit_Server_VM/17.0.9+9-Debian-1deb12u1 Java/17.0.9 vendor/Debian io/sync http/Apache cfg/retry-mode/standard
// X-Amz-Date: 20231117T174451Z
// X-Amz-Security-Token: FwoGZXIvYXdzEOb//////////wEaDBrHO9QRxjhhmtT9GiL3AZn4fzXmTL66XeZzOFPhM3CXiZj9pmqPpXepFkJvz7rRzkmSU5wB1+oxedTfVojjUIKlXK8wiWcIOd1yTeW4bFR0gMoRT/UDAvoIPc8VYfPwVhuAjTLdflfRc4aviLPPtUnPGue86yAdvYIZJna9FBB4Ltb/eTGsxCYsd7LH2qaobGJHq0UfQ+haSLSHLaWJeUY6f0xMHA3ZVgStrh9dNi0DXmSSu1bVwtmor+Io//GKb06/RjcejLbjHp2ZMrHChiSQPAyPjoRPGO71df5SKGgQtzAtAxf/9OsiFkD8U0+gPegL7iwDDb0HycXwBEs4kLeN9ApUITcosr+/qgYyMqFaJTF649WUQwy398cjXdC3wKR6YGkobD9ffasNMsqBC8JLiLrn8yIDAf/BAlyzJO7o
// Content-Length: 114
// Connection: Close
// Region: eu-central-1
// User: ASIATJV5PDKHUCV346GW
// RequestId: 08155120-3145-40f2-8100-34e7e8f33004
#define CREATE_QUEUE_REQUEST "Action=CreateQueue" \
                                "&QueueName=TestQueue" \
                                "&Attribute.1.Name=VisibilityTimeout" \
                                "&Attribute.1.Value=40" \
                                "&Tag.Key=QueueType" \
                                "&Tag.Value=Production"
#define LIST_QUEUE_REQUEST "Action=ListQueues"

namespace AwsMock::Service {

  class SQSServerJavaTest : public ::testing::Test {

  protected:

    void SetUp() override {

      // Set log level
      Core::LogStream::SetGlobalLevel("error");

      // Create some test objects
      _extraHeaders["Authorization"] =
          "AWS4-HMAC-SHA256 Credential=none/20230618/eu-central-1/sqs/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840";
      _extraHeaders["User-Agent"] =
          "aws-sdk-cpp";

      // Define endpoint. This is the endpoint of the SQS server, not the gateway
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
    }

    Core::CurlUtils _curlUtils;
    std::string _testFile, _endpoint;
    std::map<std::string, std::string> _extraHeaders;
    Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::SQSDatabase _database = Database::SQSDatabase(_configuration);
    SQSServer _sqsServer = SQSServer(_configuration, _metricService);
  };

  TEST_F(SQSServerJavaTest, QueueCreateTest) {

    // arrange

    // act
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _endpoint + "/", _extraHeaders, CREATE_QUEUE_REQUEST);
    Database::Entity::SQS::QueueList queueList = _database.ListQueues();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_EQ(1, queueList.size());
  }

  TEST_F(SQSServerJavaTest, QueueListTest) {

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

  TEST_F(SQSServerJavaTest, QueueDeleteTest) {

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

#endif // AWMOCK_SQS_JAVA_SERVERTEST_H