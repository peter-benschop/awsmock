//
// Created by vogje01 on 21/10/2023.
//

#ifndef AWMOCK_SQS_SPRING_SERVER_TEST_H
#define AWMOCK_SQS_SPRING_SERVER_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include "awsmock/service/sqs/SQSServer.h"
#include <awsmock/core/Configuration.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/repository/S3Database.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define TEST_QUEUE std::string("test-queue")
#define TEST_MESSAGE std::string("{\"testKey\": \"testValue\"}")
#define TEST_PORT 10100

namespace AwsMock::Service {

    /**
   * Tests the aws-sdk-java interface to the AwsMock system.
   *
   * <p>The aws-mock-java-test.jar file should be installed in <pre>/usr/local/lib</pre>.</p>
   *
   */
    class SQSServerSpringTest : public ::testing::Test {

      protected:

        void SetUp() override {

            // General configuration
            _region = _configuration.getString("awsmock.region", "eu-central-1");

            // Define endpoint. This is the endpoint of the SQS server, not the gateway
            _configuration.setInt("awsmock.service.sqs.http.port", TEST_PORT);
            _configuration.setString("awsmock.service.sqs.http.host", "localhost");
            _configuration.setInt("awsmock.service.gateway.http.port", TEST_PORT);
            _configuration.setString("awsmock.service.gateway.http.host", "localhost");

            // Set base command
            _basePath = "http://localhost:" + std::to_string(TEST_PORT + 1) + "/api/";

            // Start HTTP manager
            _sqsServer = std::make_unique<SQSServer>(_configuration);
            _sqsServer->Start();
        }

        void TearDown() override {
            _sqsDatabase.DeleteAllMessages();
            _sqsDatabase.DeleteAllQueues();
            _sqsServer->Stop();
        }

        Core::CurlResponse SendPostCommand(const std::string &url, const std::string &payload) {
            Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _basePath + url, {}, payload);
            log_debug << "Status: " << response.statusCode << " output: " << response.output;
            return response;
        }

        Core::CurlResponse SendGetCommand(const std::string &url, const std::string &payload) {
            Core::CurlResponse response = _curlUtils.SendHttpRequest("GET", _basePath + url, {}, payload);
            log_debug << "Status: " << response.statusCode << " output: " << response.output;
            return response;
        }

        Core::CurlUtils _curlUtils;
        std::string _basePath, _region;
        Core::Configuration &_configuration = Core::Configuration::instance();
        Core::MetricService &_metricService = Core::MetricService::instance();
        Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
        std::unique_ptr<SQSServer> _sqsServer;
    };

    TEST_F(SQSServerSpringTest, SQSCreateQueueTest) {

        // arrange

        // act
        Core::CurlResponse result = SendPostCommand("sqs/createQueue", TEST_QUEUE);
        std::string queueUrl = result.output;

        // assert
        EXPECT_TRUE(result.statusCode == 200);
        EXPECT_FALSE(queueUrl.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(queueUrl, TEST_QUEUE));
    }

    TEST_F(SQSServerSpringTest, SQSGetQueueUrlTest) {

        // arrange
        Core::CurlResponse result = SendPostCommand("sqs/createQueue", TEST_QUEUE);
        EXPECT_EQ(200, result.statusCode);

        // act
        Core::CurlResponse getUrlResult = SendGetCommand("sqs/getQueueUrl?queueName=" + Core::StringUtils::UrlEncode(TEST_QUEUE), {});
        std::string queueUrl = result.output;

        // assert
        EXPECT_TRUE(getUrlResult.statusCode == 200);
        EXPECT_FALSE(queueUrl.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(queueUrl, TEST_QUEUE));
    }

    TEST_F(SQSServerSpringTest, SQSGetAllQueueAttributes) {

        // arrange
        Core::CurlResponse result = SendPostCommand("sqs/createQueue", TEST_QUEUE);
        EXPECT_EQ(200, result.statusCode);
        std::string queueUrl = result.output;

        // act
        Core::CurlResponse resultQueueAttributes = SendPostCommand("sqs/getAllQueueAttributes?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), {});
        std::string queueAttributes = resultQueueAttributes.output;

        // assert
        EXPECT_TRUE(result.statusCode == 200);
        EXPECT_TRUE(!queueAttributes.empty());
    }

    TEST_F(SQSServerSpringTest, SQSGetSingleQueueAttributes) {

        // arrange
        Core::CurlResponse result = SendPostCommand("sqs/createQueue", TEST_QUEUE);
        EXPECT_EQ(200, result.statusCode);
        std::string queueUrl = result.output;

        // act
        Core::CurlResponse resultQueueAttributes = SendGetCommand("sqs/getSingleQueueAttribute?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&attributeName=" + Core::StringUtils::UrlEncode("APPROXIMATE_NUMBER_OF_MESSAGES"), {});
        std::string queueAttributes = resultQueueAttributes.output;

        // assert
        EXPECT_TRUE(result.statusCode == 200);
        EXPECT_TRUE(!queueAttributes.empty());
    }

    TEST_F(SQSServerSpringTest, SQSSendMessageTest) {

        // arrange
        Core::CurlResponse result = SendPostCommand("sqs/createQueue", TEST_QUEUE);
        EXPECT_EQ(200, result.statusCode);
        std::string queueUrl = result.output;

        // act
        Core::CurlResponse sendResult = SendPostCommand("sqs/sendMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), TEST_MESSAGE);
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();

        // assert
        EXPECT_TRUE(result.statusCode == 200);
        EXPECT_EQ(1, messageList.size());
    }

    TEST_F(SQSServerSpringTest, SQSTemplateTest) {

        // arrange
        Core::CurlResponse createResult = SendPostCommand("sqs/createQueue", TEST_QUEUE);
        EXPECT_EQ(200, createResult.statusCode);
        std::string queueUrl = createResult.output;

        // act
        Core::CurlResponse result = SendPostCommand("sqs/sqsTemplate", TEST_MESSAGE);
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();

        // assert
        EXPECT_TRUE(result.statusCode == 200);
        EXPECT_EQ(1, messageList.size());
    }

}// namespace AwsMock::Service

#endif// AWMOCK_SQS_SPRING_SERVER_TEST_H