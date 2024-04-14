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
#include <awsmock/repository/S3Database.h>
#include "awsmock/service/cognito/CognitoServer.h"
#include "awsmock/service/cognito/CognitoService.h"

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define ACCOUNT_ID "000000000000"
#define USER_NAME std::string("test-user")
#define USER_POOL_NAME std::string("test-user-pool")

namespace AwsMock::Service {

  /**
   * AwsMock cognito integration test.
   */
  class CognitoServerCliTest : public ::testing::Test {

  protected:

    void SetUp() override {

      // Define endpoint
      std::string _port = _configuration.getString("awsmock.service.cognito.port", std::to_string(COGNITO_DEFAULT_PORT));
      std::string _host = _configuration.getString("awsmock.service.cognito.host", COGNITO_DEFAULT_HOST);
      _configuration.setString("awsmock.service.gateway.port", _port);
      _accountId = _configuration.getString("awsmock.account.userPoolId", ACCOUNT_ID);
      _endpoint = "http://" + _host + ":" + _port;

      // Start HTTP manager
      _dynamodbServer.Start();
    }

    void TearDown() override {
      _database.DeleteAllUsers();
      _database.DeleteAllUserPools();
      _dynamodbServer.StopServer();
    }

    std::string _endpoint, _accountId;
    Core::Configuration& _configuration = Core::Configuration::instance();
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::CognitoDatabase _database = Database::CognitoDatabase();
    CognitoServer _dynamodbServer = CognitoServer(_configuration, _metricService);
  };

  TEST_F(CognitoServerCliTest, UserPoolCreateTest) {

    // arrange

    // act
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();

    // assert
    EXPECT_EQ(0, createResult.status);
    EXPECT_EQ(1, userPoolList.size());
  }

  TEST_F(CognitoServerCliTest, UserPoolListTest) {

    // arrange
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult listResult = Core::TestUtils::SendCliCommand("aws cognito-idp list-user-pools --max-results 10 --endpoint " + _endpoint);

    // assert
    EXPECT_EQ(0, listResult.status);
    EXPECT_FALSE(listResult.output.empty());
    EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, USER_POOL_NAME));
  }

  TEST_F(CognitoServerCliTest, UserPoolDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);
    Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
    std::string userPoolId = createdPoolList.front().userPoolId;

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("aws cognito-idp delete-user-pool --user-pool-userPoolId " + userPoolId + "  --endpoint " + _endpoint);
    Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(0, userPoolList.size());
  }

  TEST_F(CognitoServerCliTest, UserCreateTest) {

    // arrange
    Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createUserPoolResult.status);
    Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
    std::string userPoolId = createdPoolList.front().userPoolId;

    // act
    Core::ExecResult createUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-create-user --user-pool-userPoolId " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
    Database::Entity::Cognito::UserList userList = _database.ListUsers();

    // assert
    EXPECT_EQ(0, createUserResult.status);
    EXPECT_EQ(1, userList.size());
  }

  TEST_F(CognitoServerCliTest, UserDeleteTest) {

    // arrange
    Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createUserPoolResult.status);
    Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
    std::string userPoolId = createdPoolList.front().userPoolId;
    Core::ExecResult createUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-create-user --user-pool-userPoolId " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createUserPoolResult.status);

    // act
    Core::ExecResult deleteUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-delete-user --user-pool-userPoolId " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
    Database::Entity::Cognito::UserList userList = _database.ListUsers();

    // assert
    EXPECT_EQ(0, deleteUserResult.status);
    EXPECT_EQ(0, userList.size());
  }

} // namespace AwsMock::Service

#endif // AWMOCK_COGNITO_SERVER_CLI_TEST_H