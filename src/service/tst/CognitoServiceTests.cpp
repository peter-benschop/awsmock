//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_SERVICE_COGNITOSERVICETEST_H
#define AWMOCK_SERVICE_COGNITOSERVICETEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/repository/CognitoDatabase.h>
#include <awsmock/service/CognitoService.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define USER_POOL_NAME "test-user-pool"

namespace AwsMock::Service {

  class CognitoServiceTest : public ::testing::Test {

  protected:

    void SetUp() override {
      // General configuration
      _region = _configuration.getString("awsmock.region", "eu-central-1");
    }

    void TearDown() override {
      _database.DeleteAllUserPools();
    }

    std::string _region;
    Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
    Database::CognitoDatabase _database = Database::CognitoDatabase(_configuration);
    CognitoService _service = CognitoService(_configuration);
    std::string testFile;
  };

  TEST_F(CognitoServiceTest, UserPoolCreateTest) {

    // arrange
    Dto::Cognito::CreateUserPoolRequest createRequest = {.region=_region, .name=USER_POOL_NAME};

    // act
    Dto::Cognito::CreateUserPoolResponse createResponse = _service.CreateUserPool(createRequest);
    long userPoolCount = _database.CountUserPools();

    // assert
    EXPECT_TRUE(createResponse.name == USER_POOL_NAME);
    EXPECT_TRUE(createResponse.region == _region);
    EXPECT_EQ(1, userPoolCount);
  }

  TEST_F(CognitoServiceTest, UserPoolListTest) {

    // arrange
    Dto::Cognito::CreateUserPoolRequest createRequest = {.region=_region, .name=USER_POOL_NAME};
    Dto::Cognito::CreateUserPoolResponse createResponse = _service.CreateUserPool(createRequest);

    // act
    Dto::Cognito::ListUserPoolRequest listRequest = {.region=_region, .maxResults=10};
    Dto::Cognito::ListUserPoolResponse listResponse = _service.ListUserPools(listRequest);

    // assert
    EXPECT_FALSE(listResponse.userPools.empty());
    EXPECT_TRUE(listResponse.userPools.front().name == USER_POOL_NAME);
  }

  TEST_F(CognitoServiceTest, UserPoolDeleteTest) {

    // arrange
    Dto::Cognito::CreateUserPoolRequest createRequest = {.region=_region, .name=USER_POOL_NAME};
    Dto::Cognito::CreateUserPoolResponse createResponse = _service.CreateUserPool(createRequest);
    Database::Entity::Cognito::UserPool userPool = _database.GetUserPoolByRegionName(_region, USER_POOL_NAME);

    // act
    Dto::Cognito::DeleteUserPoolRequest deleteRequest = {.id = userPool.id};
    _service.DeleteUserPool(deleteRequest);
    long userPoolCount = _database.CountUserPools();

    // assert
    EXPECT_EQ(0, userPoolCount);
  }

} // namespace AwsMock::Service

#endif // AWMOCK_SERVICE_COGNITOSERVICETEST_H