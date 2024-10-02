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

        std::string ToJson() const {
            Poco::JSON::Object rootObject;
            rootObject.set("testKey", testKey);
            rootObject.set("receiptHandle", receiptHandle);
            return Core::JsonUtils::ToJsonString(rootObject);
        }

        void FromJson(const std::string &jsonString) {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();
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
    class SQSServerJavaTest : public ::testing::Test {

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
            _gatewayServer = std::make_shared<Service::GatewayServer>();
            _gatewayServer->Initialize();
            _gatewayServer->Start();
        }

        void TearDown() override {
            _sqsDatabase.DeleteAllMessages();
            _sqsDatabase.DeleteAllQueues();
            _gatewayServer->Shutdown();
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
        Core::Configuration &_configuration = Core::Configuration::instance();
        Monitoring::MetricService &_metricService = Monitoring::MetricService::instance();
        Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
    };

    TEST_F(SQSServerJavaTest, SQSCreateQueueTest) {

        // arrange

        // act
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        std::string queueUrl = result.body;

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_FALSE(queueUrl.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(queueUrl, TEST_QUEUE));
    }

    TEST_F(SQSServerJavaTest, SQSGetQueueUrlTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        EXPECT_EQ(http::status::ok, result.statusCode);

        // act
        Core::HttpSocketResponse getUrlResult = SendGetCommand(_baseUrl + "getQueueUrl?queueName=" + Core::StringUtils::UrlEncode(TEST_QUEUE), {});
        std::string queueUrl = result.body;

        // assert
        EXPECT_TRUE(getUrlResult.statusCode == http::status::ok);
        EXPECT_FALSE(queueUrl.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(queueUrl, TEST_QUEUE));
    }

    TEST_F(SQSServerJavaTest, SQSGetAllQueueAttributes) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;

        // act
        Core::HttpSocketResponse resultQueueAttributes = SendPostCommand(_baseUrl + "getAllQueueAttributes?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), {});
        std::string queueAttributes = resultQueueAttributes.body;

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_TRUE(!queueAttributes.empty());
    }

    TEST_F(SQSServerJavaTest, SQSGetSingleQueueAttributes) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;

        // act
        Core::HttpSocketResponse resultQueueAttributes = SendGetCommand(_baseUrl + "getSingleQueueAttribute?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&attributeName=" + Core::StringUtils::UrlEncode("APPROXIMATE_NUMBER_OF_MESSAGES"), {});
        std::string queueAttributes = resultQueueAttributes.body;

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_TRUE(!queueAttributes.empty());
    }

    TEST_F(SQSServerJavaTest, SQSSetQueueAttributes) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;

        // act
        Core::HttpSocketResponse resultQueueAttributes = SendPostCommand(_baseUrl + "setQueueAttribute?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&attributeValue=3600", {});

        // assert
        EXPECT_TRUE(resultQueueAttributes.statusCode == http::status::ok);
    }

    TEST_F(SQSServerJavaTest, SQSChangeMessageVisibilityTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;
        TestMessage testMessage = {.testKey = "testKey"};
        Core::HttpSocketResponse sendResult = SendPostCommand(_baseUrl + "sendMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), testMessage.ToJson());
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();
        std::string receiptHandle = messageList[0].receiptHandle;

        // act
        Core::HttpSocketResponse resultQueueAttributes = SendPostCommand(_baseUrl + "changeVisibility?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&visibility=3600&receiptHandle=" + Core::StringUtils::UrlEncode(receiptHandle), {});

        // assert
        EXPECT_TRUE(resultQueueAttributes.statusCode == http::status::ok);
    }

    TEST_F(SQSServerJavaTest, SQSSendMessageTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
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

    TEST_F(SQSServerJavaTest, SQSSendMessageAttributeTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;

        // act
        TestMessage testMessage = {.testKey = "testKey"};
        Core::HttpSocketResponse sendResult = SendPostCommand(_baseUrl + "sendMessageAttributes?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), testMessage.ToJson());
        EXPECT_EQ(http::status::ok, sendResult.statusCode);
        Core::HttpSocketResponse receiveResult = SendGetCommand(_baseUrl + "receiveMessages?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&maxMessages=10&maxWaitTime=5", {});
        EXPECT_EQ(http::status::ok, receiveResult.statusCode);
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();
        EXPECT_EQ(1, messageList.size());
        Database::Entity::SQS::Message message = messageList.front();

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_EQ(1, messageList.size());
        EXPECT_EQ(5, message.attributes.size());
    }

    TEST_F(SQSServerJavaTest, SQSMessageReceiveTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;
        TestMessage testMessage = {.testKey = "testKey"};
        Core::HttpSocketResponse sendResult = SendPostCommand(_baseUrl + "sendMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), testMessage.ToJson());

        // act
        Core::HttpSocketResponse receiveResult = SendGetCommand(_baseUrl + "receiveMessages?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&maxMessages=10&maxWaitTime=5", {});
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();
        EXPECT_EQ(1, messageList.size());
        Database::Entity::SQS::Message message = messageList.front();

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_EQ(1, messageList.size());
        EXPECT_TRUE(message.status == Database::Entity::SQS::MessageStatus::INVISIBLE);
    }

    TEST_F(SQSServerJavaTest, SQSPurgeQueueTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        EXPECT_EQ(http::status::ok, result.statusCode);
        std::string queueUrl = result.body;
        TestMessage testMessage = {.testKey = "testKey"};
        Core::HttpSocketResponse sendResult = SendPostCommand(_baseUrl + "sendMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), testMessage.ToJson());

        // act
        Core::HttpSocketResponse purgeResult = SendGetCommand(_baseUrl + "purgeQueue?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), {});
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_EQ(0, messageList.size());
    }

    TEST_F(SQSServerJavaTest, SQSTemplateTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
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

    TEST_F(SQSServerJavaTest, SQSDeleteMessageTest) {

        // arrange
        TestMessage testMessage = {.testKey = "testKey"};
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        EXPECT_EQ(http::status::ok, createResult.statusCode);
        std::string queueUrl = createResult.body;
        Core::HttpSocketResponse sendResult = SendPostCommand(_baseUrl + "sendMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), testMessage.ToJson());
        EXPECT_EQ(http::status::ok, sendResult.statusCode);
        std::string messageId = sendResult.body;
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();
        EXPECT_EQ(1, messageList.size());

        // act
        std::string receiptHandle = messageList[0].receiptHandle;
        Core::HttpSocketResponse deleteResult = SendDeleteCommand(_baseUrl + "deleteMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&receiptHandle=" + Core::StringUtils::UrlEncode(receiptHandle), {});
        messageList = _sqsDatabase.ListMessages();

        // assert
        EXPECT_TRUE(deleteResult.statusCode == http::status::ok);
        EXPECT_EQ(0, messageList.size());
    }

    TEST_F(SQSServerJavaTest, SQSDeleteMessageBatchTest) {

        // arrange
        TestMessage testMessage = {.testKey = "testKey"};
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createQueue?queueName=" + TEST_QUEUE, {});
        EXPECT_EQ(http::status::ok, createResult.statusCode);
        std::string queueUrl = createResult.body;
        Core::HttpSocketResponse sendResult1 = SendPostCommand(_baseUrl + "sendMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), testMessage.ToJson());
        EXPECT_EQ(http::status::ok, sendResult1.statusCode);
        Core::HttpSocketResponse sendResult2 = SendPostCommand(_baseUrl + "sendMessage?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl), testMessage.ToJson());
        EXPECT_EQ(http::status::ok, sendResult2.statusCode);
        Database::Entity::SQS::MessageList messageList = _sqsDatabase.ListMessages();
        EXPECT_EQ(2, messageList.size());

        // act
        std::string receiptHandle1 = messageList[0].receiptHandle;
        std::string receiptHandle2 = messageList[1].receiptHandle;
        Core::HttpSocketResponse deleteResult = SendDeleteCommand(_baseUrl + "deleteMessageBatch?queueUrl=" + Core::StringUtils::UrlEncode(queueUrl) + "&receiptHandle1=" + Core::StringUtils::UrlEncode(receiptHandle1) + "&receiptHandle2=" + Core::StringUtils::UrlEncode(receiptHandle2), {});
        messageList = _sqsDatabase.ListMessages();

        // assert
        EXPECT_TRUE(deleteResult.statusCode == http::status::ok);
        EXPECT_EQ(0, messageList.size());
    }

}// namespace AwsMock::Service

#endif// AWMOCK_SQS_SPRING_SERVER_TEST_H