//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_COGNITO_SERVER_CLI_TEST_H
#define AWMOCK_COGNITO_SERVER_CLI_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/TestUtils.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/repository/DynamoDbDatabase.h>
#include <awsmock/service/dynamodb/DynamoDbServer.h>
#include <awsmock/service/gateway/GatewayServer.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define ACCOUNT_ID "000000000000"
#define USER_NAME std::string("test-user")
#define USER_POOL_NAME std::string("test-user-pool")

namespace AwsMock::Service {

    /**
   * AwsMock DynamoDB integration test.
   */
    class DynamoDbServerCliTest : public ::testing::Test {

      protected:

        void SetUp() override {

            // Define endpoint
            std::string _port = _configuration.getString("awsmock.service.dynamodb.http.port", std::to_string(DYNAMODB_DEFAULT_PORT));
            std::string _host = _configuration.getString("awsmock.service.dynamodb.http.host", DYNAMODB_DEFAULT_HOST);

            // Setup gateway
            _configuration.setString("awsmock.service.gateway.http.port", _port);
            _endpoint = "http://" + _host + ":" + _port;

            // Get account ID
            _accountId = _configuration.getString("awsmock.account.id", ACCOUNT_ID);

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(ioc);
            _gatewayServer->Initialize();
            _gatewayServer->Start();
        }

        void TearDown() override {
            _database.DeleteAllTables();
            Core::ExecResult deleteResult1 = Core::SystemUtils::Exec("aws dynamodb delete-table --table-name test-table1 --endpoint-url http://localhost:8000");
            EXPECT_EQ(0, deleteResult1.status);
            _gatewayServer->Shutdown();
        }

        boost::asio::io_context ioc{10};
        std::string _endpoint, _accountId;
        Core::Configuration &_configuration = Core::Configuration::instance();
        Database::DynamoDbDatabase &_database = Database::DynamoDbDatabase::instance();
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
    };

    TEST_F(DynamoDbServerCliTest, TableCreateTest) {

        // arrange

        // act
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand(
                "aws dynamodb create-table --table-name test-table1 --attribute-definitions AttributeName=orgaNr,AttributeType=N --key-schema AttributeName=orgaNr,KeyType=HASH --provisioned-throughput ReadCapacityUnits=1,WriteCapacityUnits=1 --endpoint " + _endpoint);
        Database::Entity::DynamoDb::TableList tableList = _database.ListTables();

        // assert
        EXPECT_EQ(0, createResult.status);
        EXPECT_EQ(1, tableList.size());
    }

    TEST_F(DynamoDbServerCliTest, TableListTest) {

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand(
                "aws dynamodb create-table --table-name test-table1 --attribute-definitions AttributeName=orgaNr,AttributeType=N --key-schema AttributeName=orgaNr,KeyType=HASH --provisioned-throughput ReadCapacityUnits=1,WriteCapacityUnits=1 --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);
        Poco::Thread::sleep(2000);
        Database::Entity::DynamoDb::TableList tableList = _database.ListTables();
        EXPECT_EQ(1, tableList.size());

        // act
        Core::ExecResult listResult = Core::TestUtils::SendCliCommand("aws dynamodb list-tables --max-items 10 --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, listResult.status);
        EXPECT_FALSE(listResult.output.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, "test-table1"));
    }

}// namespace AwsMock::Service

#endif// AWMOCK_COGNITO_SERVER_CLI_TEST_H