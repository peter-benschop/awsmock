//
// Created by vogje01 on 21/10/2023.
//

#ifndef AWMOCK_SERVICE_SNS_CLI_INTEGRATION_TEST_H
#define AWMOCK_SERVICE_SNS_CLI_INTEGRATION_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/dto/sqs/CreateQueueResponse.h>
#include <awsmock/repository/SNSDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/gateway/GatewayServer.h>
#include <awsmock/service/sns/SNSServer.h>
#include <awsmock/service/sqs/SQSServer.h>

#define TEST_TOPIC std::string("test-topic")

namespace AwsMock::Service {

    class SNSServerCliTest : public ::testing::Test {

      protected:

        void SetUp() override {

            // Define endpoint. This is the endpoint of the SQS server, not the gateway
            const std::string _port = _configuration.GetValueString("awsmock.modules.sqs.http.port");
            const std::string _host = _configuration.GetValueString("awsmock.modules.sqs.http.host");

            // Set test config
            _configuration.SetValue("awsmock.service.gateway.http.port", _port);
            _endpoint = "http://" + _host + ":" + _port;

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(_ios);
        }

        void TearDown() override {
            _snsDatabase.DeleteAllMessages();
            _snsDatabase.DeleteAllTopics();
            _sqsDatabase.DeleteAllMessages();
            _sqsDatabase.DeleteAllQueues();
        }

        static std::string GetTopicArn(const std::string &jsonString) {

            std::string topicArn;
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

            try {

                Poco::JSON::Array::Ptr topicsArray = rootObject->getArray("Topics");
                if (topicsArray != nullptr) {
                    for (const auto &it: *topicsArray) {
                        const auto &object = it.extract<Poco::JSON::Object::Ptr>();
                        Core::JsonUtils::GetJsonValueString("TopicArn", object, topicArn);
                    }
                }

            } catch (Poco::Exception &exc) {
                throw Core::ServiceException(exc.message(), 500);
            }
            return topicArn;
        }

        static std::string GetMessageId(const std::string &jsonString) {

            std::string messageId;
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

            try {

                Core::JsonUtils::GetJsonValueString("MessageId", rootObject, messageId);

            } catch (Poco::Exception &exc) {
                throw Core::ServiceException(exc.message());
            }
            return messageId;
        }

        static std::string GetQueueUrl(const std::string &jsonString) {

            std::string queueUrl;
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

            try {

                Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);

            } catch (Poco::Exception &exc) {
                throw Core::ServiceException(exc.message());
            }
            return queueUrl;
        }

        static std::string GetSubscriptionArn(const std::string &jsonString) {

            std::string subscriptionArn;
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(jsonString);
            const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

            try {

                Core::JsonUtils::GetJsonValueString("SubscriptionArn", rootObject, subscriptionArn);

            } catch (Poco::Exception &exc) {
                throw Core::ServiceException(exc.message());
            }
            return subscriptionArn;
        }

        std::string _endpoint;
        boost::asio::io_service _ios{10};
        Core::Configuration &_configuration = Core::Configuration::instance();
        Database::SNSDatabase &_snsDatabase = Database::SNSDatabase::instance();
        Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
    };

    TEST_F(SNSServerCliTest, TopicCreateTest) {

        // arrange

        // act
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws sns create-topic --name " + TEST_TOPIC + " --endpoint " + _endpoint);
        Database::Entity::SNS::TopicList topicList = _snsDatabase.ListTopics();

        // assert
        EXPECT_EQ(0, createResult.status);
        EXPECT_EQ(1, topicList.size());
        EXPECT_TRUE(Core::StringUtils::Contains(createResult.output, TEST_TOPIC));
    }

    TEST_F(SNSServerCliTest, TopicListTest) {

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws sns create-topic --name " + TEST_TOPIC + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);

        // act
        Core::ExecResult listResult = Core::TestUtils::SendCliCommand("aws sns list-topics --endpoint " + _endpoint);
        Database::Entity::SNS::TopicList topicList = _snsDatabase.ListTopics();

        // assert
        EXPECT_EQ(0, listResult.status);
        EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, TEST_TOPIC));
    }

    TEST_F(SNSServerCliTest, TopicSubscribeTest) {

        // arrange
        Core::ExecResult createTopicResult = Core::TestUtils::SendCliCommand("aws sns create-topic --name " + TEST_TOPIC + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createTopicResult.status);
        Core::ExecResult listResult = Core::TestUtils::SendCliCommand("aws sns list-topics --endpoint " + _endpoint);
        EXPECT_EQ(0, listResult.status);
        std::string topicArn = GetTopicArn(listResult.output);

        Core::ExecResult createQueueResult = Core::TestUtils::SendCliCommand("aws sqs create-queue --queue-name test-queue --endpoint " + _endpoint);
        EXPECT_EQ(0, createQueueResult.status);
        std::string queueUrl = GetQueueUrl(createQueueResult.output);

        // act
        Core::ExecResult subscribeResult = Core::TestUtils::SendCliCommand("aws sns subscribe --topic-arn " + topicArn + " --protocol sqs --endpoint-url " + queueUrl + " --endpoint " + _endpoint);
        std::string subscriptionArn = GetSubscriptionArn(subscribeResult.output);

        // assert
        EXPECT_EQ(0, subscribeResult.status);
        EXPECT_FALSE(subscribeResult.output.empty());
        EXPECT_FALSE(subscriptionArn.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(subscriptionArn, "test-topic"));
    }

    TEST_F(SNSServerCliTest, TopicUnsubscribeTest) {

        // arrange
        // create topic
        Core::ExecResult createTopicResult = Core::TestUtils::SendCliCommand("aws sns create-topic --name " + TEST_TOPIC + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createTopicResult.status);
        Core::ExecResult listResult = Core::TestUtils::SendCliCommand("aws sns list-topics --endpoint " + _endpoint);
        EXPECT_EQ(0, listResult.status);
        std::string topicArn = GetTopicArn(listResult.output);

        // create queue
        Core::ExecResult createQueueResult = Core::TestUtils::SendCliCommand("aws sqs create-queue --queue-name test-queue --endpoint " + _endpoint);
        EXPECT_EQ(0, createQueueResult.status);
        std::string queueUrl = GetQueueUrl(createQueueResult.output);

        // subscribe
        Core::ExecResult subscribeResult = Core::TestUtils::SendCliCommand("aws sns subscribe --topic-arn " + topicArn + " --protocol sqs --endpoint-url " + queueUrl + " --endpoint " + _endpoint);
        std::string subscriptionArn = GetSubscriptionArn(subscribeResult.output);

        // act
        Core::ExecResult unsubscribeResult = Core::TestUtils::SendCliCommand("aws sns unsubscribe --subscription-arn " + subscriptionArn + " --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, unsubscribeResult.status);
        EXPECT_TRUE(unsubscribeResult.output.empty());
    }

    TEST_F(SNSServerCliTest, TopicDeleteTest) {

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws sns create-topic --name " + TEST_TOPIC + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);
        Core::ExecResult listResult = Core::TestUtils::SendCliCommand("aws sns list-topics --endpoint " + _endpoint);
        EXPECT_EQ(0, listResult.status);
        std::string topicArn = GetTopicArn(listResult.output);

        // act
        Core::ExecResult result = Core::TestUtils::SendCliCommand("aws sns delete-topic --topic-arn " + topicArn + " --endpoint " + _endpoint);
        Database::Entity::SNS::TopicList topicList = _snsDatabase.ListTopics();

        // assert
        EXPECT_EQ(0, result.status);
        EXPECT_EQ(0, topicList.size());
    }

    TEST_F(SNSServerCliTest, MessagePublishTest) {

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws sns create-topic --name " + TEST_TOPIC + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);
        Core::ExecResult listResult = Core::TestUtils::SendCliCommand("aws sns list-topics --endpoint " + _endpoint);
        EXPECT_EQ(0, listResult.status);
        std::string topicArn = GetTopicArn(listResult.output);

        // act
        Core::ExecResult result = Core::TestUtils::SendCliCommand("aws sns publish --topic-arn " + topicArn + " --message TEST-BODY --endpoint " + _endpoint);
        long messageCount = _snsDatabase.CountMessages();
        std::string messageId = GetMessageId(result.output);

        // assert
        EXPECT_EQ(0, result.status);
        EXPECT_EQ(1, messageCount);
        EXPECT_FALSE(messageId.empty());
    }

    /*  TEST_F(SNSServerCliTest, MessageDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("sqs", "aws sqs create-queue --queue-name " + TEST_TOPIC + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult sendResult = Core::TestUtils::SendCliCommand("sqs", "aws sqs send-message --queue-url " + _queueUrl + " --message-body TEST-BODY --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult receiveResult = Core::TestUtils::SendCliCommand("sqs", "aws sqs receive-message --queue-url " + _queueUrl + " --endpoint " + _endpoint);
    EXPECT_EQ(0, receiveResult.status);
    std::string receiptHandle = GetReceiptHandle(receiveResult.output);

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("sqs", "aws sqs delete-message --queue-url " + _queueUrl + " --receipt-handle " + receiptHandle + " --endpoint " + _endpoint);
    EXPECT_EQ(0, receiveResult.status);
    long messageCount = _database.CountMessages(REGION, _queueUrl);

    // assert
    EXPECT_EQ(0, messageCount);
  }*/

}// namespace AwsMock::Service

#endif// AWMOCK_SERVICE_SNS_CLI_INTEGRATION_TEST_H