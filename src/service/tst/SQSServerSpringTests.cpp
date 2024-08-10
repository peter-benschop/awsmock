//
// Created by vogje01 on 21/10/2023.
//

#ifndef AWMOCK_SQS_SPRING_SERVER_TEST_H
#define AWMOCK_SQS_SPRING_SERVER_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/HttpSocket.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/gateway/GatewayServer.h>
#include <awsmock/service/sqs/SQSServer.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define TEST_QUEUE std::string("test-queue")
#define TEST_MESSAGE std::string("{\"testKey\": \"testValue\"}")
#define TEST_PORT 10100

namespace AwsMock::Service {

    namespace http = boost::beast::http;

    struct TestMessage {

        std::string testKey;
        std::string receiptHandle;

        std::string ToJson() {
            Poco::JSON::Object rootObject;
            rootObject.set("testKey", testKey);
            rootObject.set("receiptHandle", receiptHandle);
            return Core::JsonUtils::ToJsonString(rootObject);
        }

        void FromJson(const std::string &jsonString) {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
            const Poco::JSON::Object::Ptr &rootObject = result.extract<Poco::JSON::Object::Ptr>();
            Core::JsonUtils::GetJsonValueString("testKey", rootObject, testKey);
            Core::JsonUtils::GetJsonValueString("receiptHandle", rootObject, receiptHandle);
        }
    };

    struct TestMessageList {

        std::vector<TestMessage> messageList;

        std::string ToJson() {
            Poco::JSON::Array rootArray;
            for (const auto &message: messageList) {
                Poco::JSON::Object messageObject;
                messageObject.set("testKey", message.testKey);
                messageObject.set("receiptHandle", message.receiptHandle);
                rootArray.add(messageObject);
            }
            return Core::JsonUtils::ToJsonString(rootArray);
        }

        void FromJson(const std::string &jsonString) {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
            Poco::JSON::Array::Ptr rootArray = result.extract<Poco::JSON::Array::Ptr>();
            if (!rootArray.isNull()) {
                for (size_t i = 0; i < rootArray->size(); i++) {
                    std::string testKey, receiptHandle;
                    Poco::JSON::Object::Ptr messageObject = rootArray->getObject(i);
                    Core::JsonUtils::GetJsonValueString("testKey", messageObject, testKey);
                    Core::JsonUtils::GetJsonValueString("receiptHandle", messageObject, receiptHandle);
                    messageList.push_back({.testKey = testKey, .receiptHandle = receiptHandle});
                }
            }
        }
    };

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
            _configuration.setInt("awsmock.service.gateway.http.port", TEST_PORT + 1);
            _configuration.setString("awsmock.service.gateway.http.host", "localhost");

            // Base URL
            _baseUrl = "/api/sqs/";

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(ioc);
            _gatewayServer->Initialize();
            _gatewayServer->Start();
        }

        void TearDown() override {
            _sqsDatabase.DeleteAllMessages();
            _sqsDatabase.DeleteAllQueues();
            _gatewayServer->Stop();
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

        std::string _region, _baseUrl;
        boost::asio::io_context ioc{2};
        Core::Configuration &_configuration = Core::Configuration::instance();
        Core::MetricService &_metricService = Core::MetricService::instance();
        Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
    };

    TEST_F(SQSServerSpringTest, SQSCreateQueueTest) {

        // arrange

        // act
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue", TEST_QUEUE);
        std::string queueUrl = result.body;

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_FALSE(queueUrl.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(queueUrl, TEST_QUEUE));
    }

    TEST_F(SQSServerSpringTest, SQSGetQueueUrlTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue", TEST_QUEUE);
        EXPECT_EQ(http::status::ok, result.statusCode);

        // act
        Core::HttpSocketResponse getUrlResult = SendGetCommand(_baseUrl + "getQueueUrl?queueName=" + Core::StringUtils::UrlEncode(TEST_QUEUE), {});
        std::string queueUrl = result.body;

        // assert
        EXPECT_TRUE(getUrlResult.statusCode == http::status::ok);
        EXPECT_FALSE(queueUrl.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(queueUrl, TEST_QUEUE));
    }

    TEST_F(SQSServerSpringTest, SQSGetAllQueueAttributes) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue", TEST_QUEUE);
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;

        // act
        Core::HttpSocketResponse resultQueueAttributes = SendPostCommand(_baseUrl + "getAllQueueAttributes?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), {});
        std::string queueAttributes = resultQueueAttributes.body;

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_TRUE(!queueAttributes.empty());
    }

    TEST_F(SQSServerSpringTest, SQSGetSingleQueueAttributes) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue", TEST_QUEUE);
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;

        // act
        Core::HttpSocketResponse resultQueueAttributes = SendGetCommand(_baseUrl + "getSingleQueueAttribute?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&attributeName=" + Core::StringUtils::UrlEncode("APPROXIMATE_NUMBER_OF_MESSAGES"), {});
        std::string queueAttributes = resultQueueAttributes.body;

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_TRUE(!queueAttributes.empty());
    }

    TEST_F(SQSServerSpringTest, SQSSendMessageTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue", TEST_QUEUE);
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;

        // act
        TestMessage testMessage = {.testKey = "testKey"};
        Core::HttpSocketResponse sendResult = SendPostCommand(_baseUrl + "sendMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), testMessage.ToJson());
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_EQ(1, messageList.size());
    }

    TEST_F(SQSServerSpringTest, SQSTemplateTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createQueue", TEST_QUEUE);
        EXPECT_EQ(http::status::ok, createResult.statusCode);
        std::string queueUrl = createResult.body;

        // act
        TestMessage testMessage = {.testKey = "testKey"};
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "sqsTemplate", testMessage.ToJson());
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_EQ(1, messageList.size());
    }

    TEST_F(SQSServerSpringTest, SQSDeleteMessageTest) {

        // arrange
        TestMessage testMessage = {.testKey = "testKey"};
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue", TEST_QUEUE);
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;
        Core::HttpSocketResponse sendResult = SendPostCommand(_baseUrl + "sendMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), testMessage.ToJson());
        EXPECT_EQ(http::status::ok, sendResult.statusCode);
        std::string messageId = sendResult.body;
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();
        EXPECT_EQ(1, messageList.size());

        // act
        std::string receiptHandle = messageList[0].receiptHandle;
        Core::HttpSocketResponse deleteResult = SendDeleteCommand(_baseUrl + "deleteMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&receiptHandle=" + Core::StringUtils::UrlEncode(receiptHandle), {});
        EXPECT_EQ(http::status::ok, deleteResult.statusCode);
        messageList = _sqsDatabase.ListMessages();

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_EQ(0, messageList.size());
    }

}// namespace AwsMock::Service

#endif// AWMOCK_SQS_SPRING_SERVER_TEST_H