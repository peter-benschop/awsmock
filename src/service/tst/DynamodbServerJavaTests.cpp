//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_DYNAMODB_SERVER_JAVA_TEST_H
#define AWMOCK_DYNAMODB_SERVER_JAVA_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/DynamoDbDatabase.h>
#include <awsmock/service/DynamoDbServer.h>

#define REGION "eu-central-1"
#define BUCKET "test-bucket"
#define KEY "testfile.json"
#define OWNER "test-owner"

namespace AwsMock::Service {

  class DynamoDbServerJavaTest : public ::testing::Test {

    protected:

      void SetUp() override {

        // Define endpoint
        std::string _port = _configuration.getString("awsmock.service.dynamodb.port", std::to_string(DYNAMODB_DEFAULT_PORT));
        std::string _host = _configuration.getString("awsmock.service.dynamodb.host", DYNAMODB_DEFAULT_HOST);
        _endpoint = "http://" + _host + ":" + _port;

        // Set base command
        _baseCommand = "java -jar /usr/local/lib/awsmock-java-test-0.0.1-SNAPSHOT-jar-with-dependencies.jar " + _endpoint + " dynamodb ";

        // Start HTTP manager
        Poco::ThreadPool::defaultPool().start(_cognitoServer);
      }

      void TearDown() override {
        //_database.DeleteAllUsers();
        _database.DeleteAllTables();
        _cognitoServer.StopServer();
      }

      std::string _endpoint, _baseCommand;
      Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration(false);
      Core::MetricService _metricService = Core::MetricService(_configuration);
      Database::DynamoDbDatabase _database = Database::DynamoDbDatabase(_configuration);
      DynamoDbServer _cognitoServer = DynamoDbServer(_configuration, _metricService);
  };

  TEST_F(DynamoDbServerJavaTest, TableCreateTest) {

    // arrange

    // act
    Core::ExecResult result = Core::SystemUtils::Exec(_baseCommand + "create-table test-table");
    Database::Entity::DynamoDb::TableList tableList = _database.ListTables();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(1, tableList.size());
  }

  /*TEST_F(CognitoServerJavaTest, UserPoolListTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + "create-user-pool test-user-pool");
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult listResult = Core::SystemUtils::Exec(_baseCommand + "list-user-pools 10");
    Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();

    // assert
    EXPECT_EQ(0, listResult.status);
    EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, "test-user-pool"));
    EXPECT_EQ(1, userPoolList.size());
  }

  TEST_F(CognitoServerJavaTest, UserPoolDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + "create-user-pool test-user-pool");
    EXPECT_EQ(0, createResult.status);
    Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();
    std::string userPoolId = userPoolList.front().id;

    // act
    Core::ExecResult deleteResult = Core::SystemUtils::Exec(_baseCommand + "delete-user-pool " + userPoolId);
    long count = _database.CountUserPools();

    // assert
    EXPECT_EQ(0, deleteResult.status);
    EXPECT_EQ(0, count);
  }

  TEST_F(CognitoServerJavaTest, UserCreateTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + "create-user-pool test-user-pool");
    EXPECT_EQ(0, createResult.status);
    Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();
    std::string userPoolId = userPoolList.front().id;

    // act
    Core::ExecResult result = Core::SystemUtils::Exec(_baseCommand + "admin-create-user " + userPoolId + " test-user");
    Database::Entity::Cognito::UserList userList = _database.ListUsers();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(1, userList.size());
  }

  TEST_F(CognitoServerJavaTest, UserDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + "create-user-pool test-user-pool");
    EXPECT_EQ(0, createResult.status);
    Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();
    std::string userPoolId = userPoolList.front().id;
    Core::ExecResult createdUser = Core::SystemUtils::Exec(_baseCommand + "admin-create-user " + userPoolId + " test-user");

    // act
    Core::ExecResult result = Core::SystemUtils::Exec(_baseCommand + "admin-delete-user " + userPoolId + " test-user");
    Database::Entity::Cognito::UserList userList = _database.ListUsers();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(0, userList.size());
  }*/

} // namespace AwsMock::Service

#endif // AWMOCK_DYNAMODB_SERVER_JAVA_TEST_H