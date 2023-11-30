//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_COGNITODATABASETEST_H
#define AWMOCK_CORE_COGNITODATABASETEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/CognitoDatabase.h>

#define USER_POOL_ID "test-user-pool_sdjhdjft"
#define USER_POOL_NAME "test-user-pool"

namespace AwsMock::Database {

  class CognitoDatabaseTest : public ::testing::Test {

  protected:

    void SetUp() override {
      _region = _configuration.getString("awsmock.region");
      _accountId = _configuration.getString("awsmock.account.id");
    }

    void TearDown() override {
      _cognitoDatabase.DeleteAllUserPools();
    }

    std::string _region;
    std::string _accountId;
    Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration();
    CognitoDatabase _cognitoDatabase = CognitoDatabase(_configuration);
  };

  TEST_F(CognitoDatabaseTest, UserPoolCreateTest) {

    // arrange
    Entity::Cognito::UserPool userPool = {.region=_region, .id=USER_POOL_ID, .name=USER_POOL_NAME};

    // act
    Entity::Cognito::UserPool result = _cognitoDatabase.CreateUserPool(userPool);

    // assert
    EXPECT_TRUE(result.name == USER_POOL_NAME);
    EXPECT_TRUE(result.id.length() > 0);
  }

  TEST_F(CognitoDatabaseTest, ListUserPoolsTest) {

    // arrange
    Entity::Cognito::UserPool userPool = {.region=_region, .id=USER_POOL_ID, .name=USER_POOL_NAME};
    Entity::Cognito::UserPool createUserPoolResult = _cognitoDatabase.CreateUserPool(userPool);

    // act
    Entity::Cognito::UserPoolList result = _cognitoDatabase.ListUserPools(_region);

    // assert
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(1, result.size());
  }

  TEST_F(CognitoDatabaseTest, UserPoolExistsTest) {

    // arrange
    Entity::Cognito::UserPool userPool = {.region=_region, .id=USER_POOL_ID, .name=USER_POOL_NAME};
    Entity::Cognito::UserPool createUserPoolResult = _cognitoDatabase.CreateUserPool(userPool);

    // act
    bool result = _cognitoDatabase.UserPoolExists(_region, USER_POOL_NAME);

    // assert
    EXPECT_TRUE(result);
  }

  TEST_F(CognitoDatabaseTest, UserPoolUpdateTest) {

    // arrange
    Entity::Cognito::UserPool userPool = {.region=_region, .id=USER_POOL_ID, .name=USER_POOL_NAME};
    Entity::Cognito::UserPool createUserPoolResult = _cognitoDatabase.CreateUserPool(userPool);

    // act
    createUserPoolResult.id = std::string(USER_POOL_NAME) + "2";
    Entity::Cognito::UserPool updateUserPoolResult = _cognitoDatabase.UpdateUserPool(createUserPoolResult);

    // assert
    EXPECT_TRUE(updateUserPoolResult.id == std::string(USER_POOL_NAME) + "2");
  }

  TEST_F(CognitoDatabaseTest, DeleteUserPoolTest) {

    // arrange
    Entity::Cognito::UserPool userPool = {.region=_region, .id=USER_POOL_ID, .name=USER_POOL_NAME};
    Entity::Cognito::UserPool createUserPoolResult = _cognitoDatabase.CreateUserPool(userPool);

    // act
    _cognitoDatabase.DeleteUserPool(createUserPoolResult.id);
    bool result = _cognitoDatabase.UserPoolExists(_region, USER_POOL_NAME);

    // assert
    EXPECT_FALSE(result);
  }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_COGNITODATABASETEST_H