//
// Created by vogje01 on 21/10/2023.
//

#ifndef AWMOCK_SERVICE_SNS_JAVA_SERVER_TEST_H
#define AWMOCK_SERVICE_SNS_JAVA_SERVER_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include "awsmock/service/gateway/GatewayServer.h"
#include "awsmock/service/sns/SNSServer.h"
#include "awsmock/service/sqs/SQSServer.h"
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/S3Database.h>

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
            std::string _port = _configuration.getString("awsmock.service.sqs.http.port", std::to_string(SQS_DEFAULT_PORT));
            std::string _host = _configuration.getString("awsmock.service.sqs.http.host", SQS_DEFAULT_HOST);
            _configuration.setString("awsmock.service.gateway.http.port", _port);
            _endpoint = "http://" + _host + ":" + _port;

            // Set base command
            _baseCommand = JAVA + " -jar /usr/local/lib/awsmock-java-test-0.0.1-SNAPSHOT-jar-with-dependencies.jar " + _endpoint;

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(ioc);
            _gatewayServer->Initialize();
            _gatewayServer->Start();
        }

        void TearDown() override {
            _snsDatabase.DeleteAllMessages();
            _snsDatabase.DeleteAllTopics();
            _sqsDatabase.DeleteAllMessages();
            _sqsDatabase.DeleteAllQueues();
            _gatewayServer->Stop();
        }

        boost::asio::io_context ioc{5};
        std::string _endpoint;
        std::string _baseCommand, _region;
        Core::Configuration &_configuration = Core::Configuration::instance();
        Database::SNSDatabase &_snsDatabase = Database::SNSDatabase::instance();
        Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
    };

    TEST_F(SNSServerJavaTest, TopicCreateTest) {

        // arrange

        // act
        Core::ExecResult result = Core::SystemUtils::Exec(_baseCommand + " sns create-topic test-topic");
        Database::Entity::SNS::TopicList topicList = _snsDatabase.ListTopics();

        // assert
        EXPECT_TRUE(result.status == 0);
        EXPECT_EQ(1, topicList.size());
    }

    TEST_F(SNSServerJavaTest, TopicListTest) {

        // arrange
        Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sns create-topic test-topic");
        EXPECT_EQ(0, createResult.status);

        // act
        Core::ExecResult listResult = Core::SystemUtils::Exec(_baseCommand + " sns list-topics");

        // assert
        EXPECT_EQ(0, listResult.status);
        EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, "test-topic"));
    }

    TEST_F(SNSServerJavaTest, TopicSubscribeTest) {

        // arrange
        Core::ExecResult createTopicResult = Core::SystemUtils::Exec(_baseCommand + " sns create-topic test-topic");
        EXPECT_EQ(0, createTopicResult.status);
        std::string topicArn = createTopicResult.output;
        Core::ExecResult createQueueResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
        EXPECT_EQ(0, createQueueResult.status);
        Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
        EXPECT_EQ(0, getQueueUrlResult.status);
        std::string queueUrl = getQueueUrlResult.output;

        // act
        Core::ExecResult subscribeResult = Core::SystemUtils::Exec(_baseCommand + " sns subscribe " + topicArn + " sqs " + queueUrl);
        std::string subscriptionArn = subscribeResult.output;

        // assert
        EXPECT_EQ(0, subscribeResult.status);
        EXPECT_FALSE(subscriptionArn.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(subscriptionArn, "test-topic"));
    }

    TEST_F(SNSServerJavaTest, TopicUnsubscribeTest) {

        // arrange
        Core::ExecResult createTopicResult = Core::SystemUtils::Exec(_baseCommand + " sns create-topic test-topic");
        EXPECT_EQ(0, createTopicResult.status);
        std::string topicArn = createTopicResult.output;
        Core::ExecResult createQueueResult = Core::SystemUtils::Exec(_baseCommand + " sqs create-queue test-queue");
        EXPECT_EQ(0, createQueueResult.status);
        Core::ExecResult getQueueUrlResult = Core::SystemUtils::Exec(_baseCommand + " sqs get-queue-url test-queue");
        EXPECT_EQ(0, getQueueUrlResult.status);
        std::string queueUrl = getQueueUrlResult.output;
        Core::ExecResult subscribeResult = Core::SystemUtils::Exec(_baseCommand + " sns subscribe " + topicArn + " sqs " + queueUrl);
        std::string subscriptionArn = subscribeResult.output;

        // act
        Core::ExecResult unsubscribeResult = Core::SystemUtils::Exec(_baseCommand + " sns unsubscribe " + subscriptionArn);

        // assert
        EXPECT_EQ(0, unsubscribeResult.status);
    }

    TEST_F(SNSServerJavaTest, TopicDeleteTest) {

        // arrange
        Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " sns create-topic test-topic");
        EXPECT_EQ(0, createResult.status);
        std::string topicArn = createResult.output;

        // act
        Core::ExecResult deleteResult = Core::SystemUtils::Exec(_baseCommand + " sns delete-topic " + topicArn);
        Database::Entity::SNS::TopicList topicList = _snsDatabase.ListTopics();

        // assert
        EXPECT_EQ(0, deleteResult.status);
        EXPECT_EQ(0, topicList.size());
    }

}// namespace AwsMock::Service

#endif// AWMOCK_SERVICE_SNS_JAVA_SERVER_TEST_H