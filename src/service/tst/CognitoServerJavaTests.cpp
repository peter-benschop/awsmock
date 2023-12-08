//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_COGNITO_SERVERJAVATEST_H
#define AWMOCK_COGNITO_SERVERJAVATEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/CognitoDatabase.h>
#include <awsmock/service/CognitoServer.h>

#define REGION "eu-central-1"
#define BUCKET "test-bucket"
#define KEY "testfile.json"
#define OWNER "test-owner"

namespace AwsMock::Service {

  class CognitoServerJavaTest : public ::testing::Test {

  protected:

    void SetUp() override {

      // Define endpoint
      std::string _port = _configuration.getString("awsmock.service.cognito.port", std::to_string(COGNITO_DEFAULT_PORT));
      std::string _host = _configuration.getString("awsmock.service.cognito.host", COGNITO_DEFAULT_HOST);
      _endpoint = "http://" + _host + ":" + _port;

      // Set base command
      _baseCommand = "java -jar /usr/local/lib/awsmock-java-test-0.0.1-SNAPSHOT-jar-with-dependencies.jar " + _endpoint + " cognito ";

      // Start HTTP manager
      Poco::ThreadPool::defaultPool().start(_cognitoServer);
    }

    void TearDown() override {
      _database.DeleteAllUserPools();
      _cognitoServer.StopServer();
    }

    std::string _endpoint, _baseCommand;
    Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration();
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::CognitoDatabase _database = Database::CognitoDatabase(_configuration);
    CognitoServer _cognitoServer = CognitoServer(_configuration, _metricService);
  };

  TEST_F(CognitoServerJavaTest, UserPoolCreateTest) {

    // arrange

    // act
    Core::ExecResult result = Core::SystemUtils::Exec(_baseCommand + "create-user-pool test-user-pool");
    Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(1, userPoolList.size());
  }

  TEST_F(CognitoServerJavaTest, UserPoolListTest) {

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

} // namespace AwsMock::Service

#endif // AWMOCK_COGNITO_SERVERJAVATEST_H