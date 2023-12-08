//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_COGNITO_SERVERCLITEST_H
#define AWMOCK_COGNITO_SERVERCLITEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/CognitoServer.h>
#include <awsmock/service/CognitoService.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define ACCOUNT_ID "000000000000"
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
      _accountId = _configuration.getString("awsmock.account.id", ACCOUNT_ID);
      _endpoint = "http://" + _host + ":" + _port;

      // Start HTTP manager
      Poco::ThreadPool::defaultPool().start(_cognitoServer);
    }

    void TearDown() override {
      _database.DeleteAllUserPools();
      _cognitoServer.StopServer();
    }

    std::string _endpoint, _accountId;
    Poco::NotificationQueue createQueue, invokeQueue;
    Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration();
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::CognitoDatabase _database = Database::CognitoDatabase(_configuration);
    CognitoServer _cognitoServer = CognitoServer(_configuration, _metricService);
  };

  TEST_F(CognitoServerCliTest, UserPoolCreateTest) {

    // arrange

    // act
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("cognito", "aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();

    // assert
    EXPECT_EQ(0, createResult.status);
    EXPECT_EQ(1, userPoolList.size());
  }

  TEST_F(CognitoServerCliTest, UserPoolListTest) {

    // arrange
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("cognito", "aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult listResult = Core::TestUtils::SendCliCommand("cognito", "aws cognito-idp list-user-pools --max-results 10 --endpoint " + _endpoint);

    // assert
    EXPECT_EQ(0, listResult.status);
    EXPECT_TRUE(listResult.output.length() > 0);
    EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, USER_POOL_NAME));
  }

  TEST_F(CognitoServerCliTest, UserPoolDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("cognito", "aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);
    Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
    std::string userPoolId = createdPoolList.front().id;

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("cognito", "aws cognito-idp delete-user-pool --user-pool-id " + userPoolId + "  --endpoint " + _endpoint);
    Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(0, userPoolList.size());
  }

} // namespace AwsMock::Service

#endif // AWMOCK_COGNITO_SERVERCLITEST_H