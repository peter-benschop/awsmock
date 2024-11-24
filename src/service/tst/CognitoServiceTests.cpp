//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_SERVICE_COGNITOSERVICETEST_H
#define AWMOCK_SERVICE_COGNITOSERVICETEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include "awsmock/service/cognito/CognitoService.h"
#include <awsmock/repository/CognitoDatabase.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define USER_NAME "test-user"
#define USER_POOL_NAME "test-user-pool"

namespace AwsMock::Service {

    class CognitoServiceTest : public ::testing::Test {

      protected:

        void SetUp() override {
            _region = _configuration.GetValueString("awsmock.region");
        }

        void TearDown() override {
            _database.DeleteAllUsers();
            _database.DeleteAllUserPools();
        }

        std::string _region;
        Core::YamlConfiguration &_configuration = Core::TestUtils::GetTestConfiguration(false);
        Database::CognitoDatabase &_database = Database::CognitoDatabase::instance();
        CognitoService _service;
    };

    TEST_F(CognitoServiceTest, UserPoolCreateTest) {

        // arrange
        Dto::Cognito::CreateUserPoolRequest createRequest = {{.region = _region}, USER_POOL_NAME};

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
        Dto::Cognito::CreateUserPoolRequest createRequest = {{.region = _region}, USER_POOL_NAME};
        Dto::Cognito::CreateUserPoolResponse createResponse = _service.CreateUserPool(createRequest);

        // act
        Dto::Cognito::ListUserPoolRequest listRequest = {{.region = _region}, 10};
        Dto::Cognito::ListUserPoolResponse listResponse = _service.ListUserPools(listRequest);

        // assert
        EXPECT_FALSE(listResponse.userPools.empty());
        EXPECT_TRUE(listResponse.userPools.front().name == USER_POOL_NAME);
    }

    TEST_F(CognitoServiceTest, UserPoolDeleteTest) {

        // arrange
        Dto::Cognito::CreateUserPoolRequest createRequest = {{.region = _region}, USER_POOL_NAME};
        Dto::Cognito::CreateUserPoolResponse createResponse = _service.CreateUserPool(createRequest);
        Database::Entity::Cognito::UserPool userPool = _database.GetUserPoolByRegionName(_region, USER_POOL_NAME);

        // act
        Dto::Cognito::DeleteUserPoolRequest deleteRequest = {.userPoolId = userPool.userPoolId};
        _service.DeleteUserPool(deleteRequest);
        long userPoolCount = _database.CountUserPools();

        // assert
        EXPECT_EQ(0, userPoolCount);
    }

    TEST_F(CognitoServiceTest, UserCreateTest) {

        // arrange
        Dto::Cognito::CreateUserPoolRequest createUserPoolRequest = {{.region = _region}, USER_POOL_NAME};
        Dto::Cognito::CreateUserPoolResponse createUserPoolResponse = _service.CreateUserPool(createUserPoolRequest);
        Database::Entity::Cognito::UserPool userPool = _database.GetUserPoolByRegionName(_region, USER_POOL_NAME);
        Dto::Cognito::AdminCreateUserRequest createUserRequest = {{.region = _region}, userPool.userPoolId, USER_NAME};

        // act
        Dto::Cognito::AdminCreateUserResponse createUserResponse = _service.AdminCreateUser(createUserRequest);
        long userCount = _database.CountUsers();

        // assert
        EXPECT_EQ(1, userCount);
    }

    TEST_F(CognitoServiceTest, UserListTest) {

        // arrange
        Dto::Cognito::CreateUserPoolRequest createUserPoolRequest = {{.region = _region}, USER_POOL_NAME};
        Dto::Cognito::CreateUserPoolResponse createUserPoolResponse = _service.CreateUserPool(createUserPoolRequest);
        Database::Entity::Cognito::UserPool userPool = _database.GetUserPoolByRegionName(_region, USER_POOL_NAME);
        Dto::Cognito::AdminCreateUserRequest createUserRequest = {{.region = _region}, userPool.userPoolId, USER_NAME};
        Dto::Cognito::AdminCreateUserResponse createUserResponse = _service.AdminCreateUser(createUserRequest);

        // act
        Dto::Cognito::ListUsersRequest listRequest = {{.region = _region}, userPool.userPoolId};
        Dto::Cognito::ListUsersResponse listResponse = _service.ListUsers(listRequest);

        // assert
        EXPECT_FALSE(listResponse.users.empty());
        EXPECT_TRUE(listResponse.users.front().userName == USER_NAME);
    }

    TEST_F(CognitoServiceTest, UserDeleteTest) {

        // arrange
        Dto::Cognito::CreateUserPoolRequest createUserPoolRequest = {{.region = _region}, USER_POOL_NAME};
        Dto::Cognito::CreateUserPoolResponse createUserPoolResponse = _service.CreateUserPool(createUserPoolRequest);
        Database::Entity::Cognito::UserPool userPool = _database.GetUserPoolByRegionName(_region, USER_POOL_NAME);
        Dto::Cognito::AdminCreateUserRequest createUserRequest = {{.region = _region}, userPool.userPoolId, USER_NAME};
        Dto::Cognito::AdminCreateUserResponse createUserResponse = _service.AdminCreateUser(createUserRequest);

        // act
        Dto::Cognito::AdminDeleteUserRequest deleteUserRequest = {{.region = _region}, userPool.userPoolId, USER_NAME};
        _service.AdminDeleteUser(deleteUserRequest);
        long userCount = _database.CountUsers();

        // assert
        EXPECT_EQ(0, userCount);
    }

}// namespace AwsMock::Service

#endif// AWMOCK_SERVICE_COGNITOSERVICETEST_H