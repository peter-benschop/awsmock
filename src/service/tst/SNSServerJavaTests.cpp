//
// Created by vogje01 on 21/10/2023.
//

#ifndef AWMOCK_SERVICE_SNS_JAVA_SERVER_TEST_H
#define AWMOCK_SERVICE_SNS_JAVA_SERVER_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/gateway/GatewayServer.h>
#include <awsmock/service/sns/SNSServer.h>
#include <awsmock/service/sqs/SQSServer.h>

#define TEST_PORT 10100
#define TEST_TOPIC std::string("test-topic")
#define TEST_QUEUE std::string("test-queue")

namespace AwsMock::Service {

    /**
   * Tests the aws-sdk-java interface to the AwsMock system.
   *
   * <p>The aws-mock-java-test.jar file should be installed in <pre>/usr/local/lib</pre>. The SNS server as well as the SQS server are started. This is needed as the SNS topic subscribe command needs a existing SQS queue.</p>
   *
   */
    class SNSServerJavaTest : public ::testing::Test {

      protected:

        void SetUp() override {

            // Define endpoint. This is the endpoint of the SQS server, not the gateway
            _configuration.SetValueInt("awsmock.service.gateway.http.port", TEST_PORT + 1);
            _configuration.SetValueBool("awsmock.service.gateway.http.host", "localhost");

            // Set base URLs
            _snsBaseUrl = "/api/sns/";
            _sqsBaseUrl = "/api/sqs/";

            // Start HTTP manager
            _gatewayServer = std::make_shared<GatewayServer>(_ios);
        }

        void TearDown() override {
            _snsDatabase.DeleteAllMessages();
            _snsDatabase.DeleteAllTopics();
            _sqsDatabase.DeleteAllMessages();
            _sqsDatabase.DeleteAllQueues();
        }

        static Core::HttpSocketResponse SendPostCommand(const std::string &url, const std::string &payload) {
            std::map<std::string, std::string> headers;
            headers[to_string(http::field::content_type)] = "application/json";
            Core::HttpSocketResponse response = Core::HttpSocket::SendJson(http::verb::post, "localhost", TEST_PORT, url, payload, headers);
            log_debug << "Status: " << response.statusCode << " body: " << response.body;
            return response;
        }

        static Core::HttpSocketResponse SendGetCommand(const std::string &url, const std::string &payload) {
            std::map<std::string, std::string> headers;
            headers[to_string(http::field::content_type)] = "application/json";
            Core::HttpSocketResponse response = Core::HttpSocket::SendJson(http::verb::get, "localhost", TEST_PORT, url, payload, headers);
            log_debug << "Status: " << response.statusCode << " body: " << response.body;
            return response;
        }

        static Core::HttpSocketResponse SendDeleteCommand(const std::string &url, const std::string &payload) {
            std::map<std::string, std::string> headers;
            headers[to_string(http::field::content_type)] = "application/json";
            Core::HttpSocketResponse response = Core::HttpSocket::SendJson(http::verb::delete_, "localhost", TEST_PORT, url, payload, headers);
            log_debug << "Status: " << response.statusCode << " body: " << response.body;
            return response;
        }

        std::string _snsBaseUrl, _sqsBaseUrl, _region;
        boost::asio::io_service _ios{10};
        Core::Configuration &_configuration = Core::Configuration::instance();
        Database::SNSDatabase &_snsDatabase = Database::SNSDatabase::instance();
        Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
        std::shared_ptr<GatewayServer> _gatewayServer;
    };

    TEST_F(SNSServerJavaTest, TopicCreateTest) {

        // arrange

        // act
        const Core::HttpSocketResponse result = SendPostCommand(_snsBaseUrl + "createTopic?name=" + Core::StringUtils::UrlEncode(TEST_TOPIC), {});
        const std::string topicArn = result.body;

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_FALSE(topicArn.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(topicArn, TEST_TOPIC));
    }

    TEST_F(SNSServerJavaTest, TopicListTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_snsBaseUrl + "createTopic?name=" + Core::StringUtils::UrlEncode(TEST_TOPIC), {});
        EXPECT_TRUE(result.statusCode == http::status::ok);
        std::string topicArn = result.body;

        // act
        Core::HttpSocketResponse listResult = SendGetCommand(_snsBaseUrl + "listTopics", {});
        EXPECT_TRUE(listResult.statusCode == http::status::ok);

        // assert
        EXPECT_EQ(1, std::stoi(listResult.body));
    }

    TEST_F(SNSServerJavaTest, TopicSubscribeTest) {

        // arrange
        Core::HttpSocketResponse createTopicResult = SendPostCommand(_snsBaseUrl + "createTopic?name=" + Core::StringUtils::UrlEncode(TEST_TOPIC), {});
        EXPECT_TRUE(createTopicResult.statusCode == http::status::ok);
        std::string topicArn = createTopicResult.body;
        Core::HttpSocketResponse createQueueResult = SendPostCommand(_sqsBaseUrl + "createQueue?queueName=" + Core::StringUtils::UrlEncode(TEST_QUEUE), {});
        EXPECT_TRUE(createQueueResult.statusCode == http::status::ok);
        std::string queueUrl = createQueueResult.body;

        // act
        Core::HttpSocketResponse subscribeResult = SendPostCommand(_snsBaseUrl + "subscribe?topicArn=" + Core::StringUtils::UrlEncode(topicArn) + "&queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&protocol=SQS", {});
        std::string subscriptionArn = subscribeResult.body;

        // assert
        EXPECT_TRUE(subscribeResult.statusCode == http::status::ok);
        EXPECT_FALSE(subscriptionArn.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(subscriptionArn, "test-topic"));
    }

    TEST_F(SNSServerJavaTest, TopicUnsubscribeTest) {

        // arrange
        Core::HttpSocketResponse createTopicResult = SendPostCommand(_snsBaseUrl + "createTopic?name=" + Core::StringUtils::UrlEncode(TEST_TOPIC), {});
        EXPECT_TRUE(createTopicResult.statusCode == http::status::ok);
        std::string topicArn = createTopicResult.body;
        Core::HttpSocketResponse createQueueResult = SendPostCommand(_sqsBaseUrl + "createQueue?queueName=" + Core::StringUtils::UrlEncode(TEST_QUEUE), {});
        EXPECT_TRUE(createQueueResult.statusCode == http::status::ok);
        std::string queueUrl = createQueueResult.body;
        Core::HttpSocketResponse subscribeResult = SendPostCommand(_snsBaseUrl + "subscribe?topicArn=" + Core::StringUtils::UrlEncode(topicArn) + "&queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&protocol=SQS", {});
        std::string subscriptionArn = subscribeResult.body;

        // act
        Core::HttpSocketResponse unsubscribeResult = SendPostCommand(_snsBaseUrl + "unsubscribe?subscriptionArn=" + Core::StringUtils::UrlEncode(subscriptionArn), {});

        // assert
        EXPECT_TRUE(unsubscribeResult.statusCode == http::status::ok);
    }

    TEST_F(SNSServerJavaTest, TopicDeleteTest) {

        // arrange
        Core::HttpSocketResponse createTopicResult = SendPostCommand(_snsBaseUrl + "createTopic?name=" + Core::StringUtils::UrlEncode(TEST_TOPIC), {});
        EXPECT_TRUE(createTopicResult.statusCode == http::status::ok);
        std::string topicArn = createTopicResult.body;

        // act
        Core::HttpSocketResponse deleteResult = SendDeleteCommand(_snsBaseUrl + "deleteTopic?topicArn=" + Core::StringUtils::UrlEncode(topicArn), {});
        Database::Entity::SNS::TopicList topicList = _snsDatabase.ListTopics();

        // assert
        EXPECT_TRUE(deleteResult.statusCode == http::status::ok);
        EXPECT_EQ(0, topicList.size());
    }

}// namespace AwsMock::Service

#endif// AWMOCK_SERVICE_SNS_JAVA_SERVER_TEST_H