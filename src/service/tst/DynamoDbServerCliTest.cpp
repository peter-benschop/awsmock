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
            std::string _port = _configuration.getString("awsmock.service.dynamodb.http.port", std::to_string(GATEWAY_DEFAULT_PORT));
            std::string _host = _configuration.getString("awsmock.service.dynamodb.http.host", GATEWAY_DEFAULT_HOST);

            // Setup gateway
            _configuration.setString("awsmock.service.gateway.http.port", _port);
            _endpoint = "http://" + _host + ":" + _port;

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(_pool);
            _gatewayServer->Initialize();
            _gatewayServer->Start();
        }

        void TearDown() override {
            _database.DeleteAllTables();
            Core::ExecResult deleteResult1 = Core::SystemUtils::Exec("aws dynamodb delete-table --table-name test-table1 --endpoint http://localhost:8000");
            _gatewayServer->Shutdown();
        }

        static std::string WriteItemFile() {
            return Core::FileUtils::CreateTempFile("json", R"({"orgaNr":{"N":"1"}})");
        }


        static std::string WriteKeyFile() {
            return Core::FileUtils::CreateTempFile("json", R"({"orgaNr":{"N":"1"}})");
        }

        std::string _endpoint;
        boost::asio::thread_pool _pool = (10);
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

        // act
        Core::ExecResult listResult = Core::TestUtils::SendCliCommand("aws dynamodb list-tables --max-items 10 --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, listResult.status);
        EXPECT_FALSE(listResult.output.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, "test-table1"));
    }

    TEST_F(DynamoDbServerCliTest, TableDescribeTest) {

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand(
                "aws dynamodb create-table --table-name test-table1 --attribute-definitions AttributeName=orgaNr,AttributeType=N --key-schema AttributeName=orgaNr,KeyType=HASH --provisioned-throughput ReadCapacityUnits=1,WriteCapacityUnits=1 --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);
        Database::Entity::DynamoDb::TableList tableList = _database.ListTables();
        EXPECT_EQ(1, tableList.size());

        // act
        Core::ExecResult describeResult = Core::TestUtils::SendCliCommand("aws dynamodb describe-table --table-name test-table1 --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, describeResult.status);
        EXPECT_FALSE(describeResult.output.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(describeResult.output, "test-table1"));
    }

    TEST_F(DynamoDbServerCliTest, TableDeleteTest) {

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand(
                "aws dynamodb create-table --table-name test-table1 --attribute-definitions AttributeName=orgaNr,AttributeType=N --key-schema AttributeName=orgaNr,KeyType=HASH --provisioned-throughput ReadCapacityUnits=1,WriteCapacityUnits=1 --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);
        Database::Entity::DynamoDb::TableList tableList = _database.ListTables();
        EXPECT_EQ(1, tableList.size());

        // act
        Core::ExecResult deleteResult = Core::TestUtils::SendCliCommand("aws dynamodb delete-table --table-name test-table1 --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, deleteResult.status);
        EXPECT_FALSE(deleteResult.output.empty());
    }

    TEST_F(DynamoDbServerCliTest, ItemPutTest) {

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand(
                "aws dynamodb create-table --table-name test-table1 --attribute-definitions AttributeName=orgaNr,AttributeType=N --key-schema AttributeName=orgaNr,KeyType=HASH --provisioned-throughput ReadCapacityUnits=1,WriteCapacityUnits=1 --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);
        Database::Entity::DynamoDb::TableList tableList = _database.ListTables();
        EXPECT_EQ(1, tableList.size());
        std::string itemFile = WriteItemFile();

        // act
        std::ofstream tmp("/tmp/debug.txt");
        tmp << "aws dynamodb put-item --table-name test-table1 --item file://" + itemFile + " --endpoint " + _endpoint << std::endl;
        tmp.close();
        Core::ExecResult itemPutResult = Core::TestUtils::SendCliCommand("aws dynamodb put-item --table-name test-table1 --item file://" + itemFile + " --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, itemPutResult.status);
        EXPECT_TRUE(itemPutResult.output.empty());
    }

    TEST_F(DynamoDbServerCliTest, ItemGetTest) {

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand(
                "aws dynamodb create-table --table-name test-table1 --attribute-definitions AttributeName=orgaNr,AttributeType=N --key-schema AttributeName=orgaNr,KeyType=HASH --provisioned-throughput ReadCapacityUnits=1,WriteCapacityUnits=1 --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);
        Database::Entity::DynamoDb::TableList tableList = _database.ListTables();
        EXPECT_EQ(1, tableList.size());
        std::string itemFile = WriteItemFile();
        Core::ExecResult itemPutResult = Core::TestUtils::SendCliCommand("aws dynamodb put-item --table-name test-table1 --item file://" + itemFile + " --endpoint " + _endpoint);
        EXPECT_EQ(0, itemPutResult.status);

        // act
        std::string keyFile = WriteKeyFile();
        Core::ExecResult itemGetResult = Core::TestUtils::SendCliCommand("aws dynamodb get-item --table-name test-table1 --key file://" + keyFile + " --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, itemGetResult.status);
        EXPECT_FALSE(itemGetResult.output.empty());
    }

    TEST_F(DynamoDbServerCliTest, ItemScanTest) {

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand(
                "aws dynamodb create-table --table-name test-table1 --attribute-definitions AttributeName=orgaNr,AttributeType=N --key-schema AttributeName=orgaNr,KeyType=HASH --provisioned-throughput ReadCapacityUnits=1,WriteCapacityUnits=1 --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);
        Database::Entity::DynamoDb::TableList tableList = _database.ListTables();
        EXPECT_EQ(1, tableList.size());
        std::string itemFile = WriteItemFile();
        Core::ExecResult itemPutResult = Core::TestUtils::SendCliCommand("aws dynamodb put-item --table-name test-table1 --item file://" + itemFile + " --endpoint " + _endpoint);
        EXPECT_EQ(0, itemPutResult.status);

        // act
        std::string keyFile = WriteKeyFile();
        Core::ExecResult scanResult = Core::TestUtils::SendCliCommand("aws dynamodb scan --table-name test-table1 --endpoint " + _endpoint);

        // assert
        EXPECT_EQ(0, scanResult.status);
        EXPECT_FALSE(scanResult.output.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(scanResult.output, "orgaNr"));
    }

}// namespace AwsMock::Service

#endif// AWMOCK_COGNITO_SERVER_CLI_TEST_H