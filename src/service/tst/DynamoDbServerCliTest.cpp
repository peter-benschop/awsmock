//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_COGNITO_SERVER_CLI_TEST_H
#define AWMOCK_COGNITO_SERVER_CLI_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/DynamoDbDatabase.h>
#include <awsmock/service/DynamoDbServer.h>

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
        std::string _port = _configuration.getString("awsmock.service.dynamodb.port", std::to_string(DYNAMODB_DEFAULT_PORT));
        std::string _host = _configuration.getString("awsmock.service.dynamodb.host", DYNAMODB_DEFAULT_HOST);
        _configuration.setString("awsmock.service.gateway.port", _port);
        _accountId = _configuration.getString("awsmock.account.id", ACCOUNT_ID);
        _endpoint = "http://" + _host + ":" + _port;

        // Start HTTP manager
        Poco::ThreadPool::defaultPool().start(_dynamodbServer);
      }

      void TearDown() override {
        _database.DeleteAllTables();
        Core::ExecResult deleteResult1 = Core::SystemUtils::Exec("aws dynamodb delete-table --table-name test-table1 --endpoint-url http://localhost:8000");
        EXPECT_EQ(0, deleteResult1.status);
        Core::ExecResult deleteResult2 = Core::SystemUtils::Exec("aws dynamodb delete-table --table-name test-table2 --endpoint-url http://localhost:8000");
        EXPECT_EQ(0, deleteResult2.status);
        _dynamodbServer.StopServer();
      }

      std::string _endpoint, _accountId;
      Poco::NotificationQueue createQueue, invokeQueue;
      Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration(false);
      Core::MetricService _metricService = Core::MetricService(_configuration);
      Database::DynamoDbDatabase _database = Database::DynamoDbDatabase(_configuration);
      DynamoDbServer _dynamodbServer = DynamoDbServer(_configuration, _metricService);
  };

  TEST_F(DynamoDbServerCliTest, TableCreateTest) {

    // arrange

    // act
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand(
      "aws dynamodb create-table --table-name test-table1 --attribute-definitions attributeName=orgaNr,AttributeType=N --key-schema attributeName=orgaNr,KeyType=HASH --provisioned-throughput ReadCapacityUnits=1,WriteCapacityUnits=1 --endpoint "
        + _endpoint);
    Database::Entity::DynamoDb::TableList tableList = _database.ListTables();

    // assert
    EXPECT_EQ(0, createResult.status);
    EXPECT_EQ(1, tableList.size());
  }

  TEST_F(DynamoDbServerCliTest, TableListTest) {

    // arrange
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand(
      "aws dynamodb create-table --table-name test-table2 --attribute-definitions attributeName=orgaNr,AttributeType=N --key-schema attributeName=orgaNr,KeyType=HASH --provisioned-throughput ReadCapacityUnits=1,WriteCapacityUnits=1 --endpoint "
        + _endpoint);
    Database::Entity::DynamoDb::TableList tableList = _database.ListTables();

    // act
    Core::ExecResult listResult = Core::TestUtils::SendCliCommand("aws dynamodb list-tables --max-items 10 --endpoint " + _endpoint);

    // assert
    EXPECT_EQ(0, listResult.status);
    EXPECT_FALSE(listResult.output.empty());
    EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, "test-table2"));
  }

/*  TEST_F(DynamoDbServerCliTest, UserPoolDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);
    Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
    std::string userPoolId = createdPoolList.front().id;

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("aws cognito-idp delete-user-pool --user-pool-id " + userPoolId + "  --endpoint " + _endpoint);
    Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(0, userPoolList.size());
  }

  TEST_F(DynamoDbServerCliTest, UserCreateTest) {

    // arrange
    Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createUserPoolResult.status);
    Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
    std::string userPoolId = createdPoolList.front().id;

    // act
    Core::ExecResult createUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-create-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
    Database::Entity::Cognito::UserList userList = _database.ListUsers();

    // assert
    EXPECT_EQ(0, createUserResult.status);
    EXPECT_EQ(1, userList.size());
  }

  TEST_F(DynamoDbServerCliTest, UserDeleteTest) {

    // arrange
    Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createUserPoolResult.status);
    Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
    std::string userPoolId = createdPoolList.front().id;
    Core::ExecResult createUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-create-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createUserPoolResult.status);

    // act
    Core::ExecResult deleteUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-delete-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
    Database::Entity::Cognito::UserList userList = _database.ListUsers();

    // assert
    EXPECT_EQ(0, deleteUserResult.status);
    EXPECT_EQ(0, userList.size());
  }*/

} // namespace AwsMock::Service

#endif // AWMOCK_COGNITO_SERVER_CLI_TEST_H