//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_COGNITO_SERVER_CLI_TEST_H
#define AWMOCK_COGNITO_SERVER_CLI_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/cognito/CognitoServer.h>
#include <awsmock/service/cognito/CognitoService.h>
#include <awsmock/service/gateway/GatewayServer.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define ACCOUNT_ID "000000000000"
#define PASSWORD std::string("test-password")
#define USER_NAME std::string("test-user")
#define GROUP_NAME std::string("test-group")
#define CLIENT_NAME std::string("test-client")
#define DOMAIN_NAME std::string("test-domain")
#define USER_POOL_NAME std::string("test-user-pool")

namespace AwsMock::Service {

    /**
     * @brief AwsMock cognito integration test.
     */
    class CognitoServerCliTest : public ::testing::Test {

      protected:

        void SetUp() override {

            // General configuration
            _region = _configuration.GetValueString("awsmock.region");

            // Define endpoint. This is the endpoint of the SQS server, not the gateway
            const std::string _port = _configuration.GetValueString("awsmock.service.sqs.http.port");
            const std::string _host = _configuration.GetValueString("awsmock.service.sqs.http.host");

            // Set test config
            _configuration.SetValue("awsmock.service.gateway.http.port", _port);
            _endpoint = "http://" + _host + ":" + _port;

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(_ios);
        }

        void TearDown() override {
            _database.DeleteAllUsers();
            _database.DeleteAllGroups();
            _database.DeleteAllUserPools();
        }

        std::string _endpoint, _accountId, _region;
        boost::asio::io_service _ios{10};
        Core::YamlConfiguration &_configuration = Core::YamlConfiguration::instance();
        Database::CognitoDatabase &_database = Database::CognitoDatabase::instance();
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
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

    TEST_F(CognitoServerCliTest, UserPoolCreateClientTest) {

        // arrange
        Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);
        Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
        std::string userPoolId = createdPoolList.front().userPoolId;

        // act
        Core::ExecResult createUserPoolClientResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool-client --user-pool-id " + userPoolId + " --client-name " + CLIENT_NAME + " --endpoint " + _endpoint);
        Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();

        // assert
        EXPECT_EQ(0, createUserPoolClientResult.status);
        EXPECT_EQ(1, userPoolList.size());
        EXPECT_FALSE(userPoolList.front().userPoolClients.empty());
    }

    TEST_F(CognitoServerCliTest, UserPoolCreateDomainTest) {

        // arrange
        Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);
        Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
        std::string userPoolId = createdPoolList.front().userPoolId;

        // act
        Core::ExecResult createUserPoolDomainResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool-domain --user-pool-id " + userPoolId + " --domain " + DOMAIN_NAME + " --endpoint " + _endpoint);
        Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();

        // assert
        EXPECT_EQ(0, createUserPoolDomainResult.status);
        EXPECT_EQ(1, userPoolList.size());
        EXPECT_TRUE(userPoolList.front().domain.domain == DOMAIN_NAME);
    }

    TEST_F(CognitoServerCliTest, UserPoolDeleteTest) {

        // arrange
        Core::ExecResult createResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createResult.status);
        Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
        std::string userPoolId = createdPoolList.front().userPoolId;

        // act
        Core::ExecResult result = Core::TestUtils::SendCliCommand("aws cognito-idp delete-user-pool --user-pool-id " + userPoolId + "  --endpoint " + _endpoint);
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
        Core::ExecResult createUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-create-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
        Database::Entity::Cognito::UserList userList = _database.ListUsers();

        // assert
        EXPECT_EQ(0, createUserResult.status);
        EXPECT_EQ(1, userList.size());
    }

    TEST_F(CognitoServerCliTest, UserEnableTest) {

        // arrange
        Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);
        Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
        std::string userPoolId = createdPoolList.front().userPoolId;
        Core::ExecResult createUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-create-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserResult.status);
        Database::Entity::Cognito::UserList userList = _database.ListUsers();
        EXPECT_EQ(1, userList.size());

        // act
        Core::ExecResult enableUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-enable-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
        userList = _database.ListUsers();

        // assert
        EXPECT_EQ(0, enableUserResult.status);
        EXPECT_EQ(1, userList.size());
        EXPECT_TRUE(userList.front().enabled);
    }

    TEST_F(CognitoServerCliTest, UserDisableTest) {

        // arrange
        Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);
        Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
        std::string userPoolId = createdPoolList.front().userPoolId;
        Core::ExecResult createUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-create-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserResult.status);
        Database::Entity::Cognito::UserList userList = _database.ListUsers();
        EXPECT_EQ(1, userList.size());
        Core::ExecResult enableUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-enable-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, enableUserResult.status);

        // act
        Core::ExecResult disableUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-disable-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
        userList = _database.ListUsers();

        // assert
        EXPECT_EQ(0, disableUserResult.status);
        EXPECT_EQ(1, userList.size());
        EXPECT_FALSE(userList.front().enabled);
    }

    TEST_F(CognitoServerCliTest, UserDeleteTest) {

        // arrange
        Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);
        Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
        std::string userPoolId = createdPoolList.front().userPoolId;
        Core::ExecResult createUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-create-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);

        // act
        Core::ExecResult deleteUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-delete-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
        Database::Entity::Cognito::UserList userList = _database.ListUsers();

        // assert
        EXPECT_EQ(0, deleteUserResult.status);
        EXPECT_EQ(0, userList.size());
    }

    TEST_F(CognitoServerCliTest, GroupCreateTest) {

        // arrange
        Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);
        Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
        std::string userPoolId = createdPoolList.front().userPoolId;

        // act
        Core::ExecResult createGroupResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-group --user-pool-id " + userPoolId + " --group-name " + GROUP_NAME + " --endpoint " + _endpoint);
        Database::Entity::Cognito::GroupList groupList = _database.ListGroups();

        // assert
        EXPECT_EQ(0, createGroupResult.status);
        EXPECT_EQ(1, groupList.size());
    }

    TEST_F(CognitoServerCliTest, GroupDeleteTest) {

        // arrange
        Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);
        Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
        std::string userPoolId = createdPoolList.front().userPoolId;
        Core::ExecResult createGroupResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-group --user-pool-id " + userPoolId + " --group-name " + GROUP_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createGroupResult.status);

        // act
        Core::ExecResult deleteGroupResult = Core::TestUtils::SendCliCommand("aws cognito-idp delete-group --user-pool-id " + userPoolId + " --group-name " + GROUP_NAME + " --endpoint " + _endpoint);
        Database::Entity::Cognito::GroupList groupList = _database.ListGroups();

        // assert
        EXPECT_EQ(0, deleteGroupResult.status);
        EXPECT_EQ(0, groupList.size());
    }

    TEST_F(CognitoServerCliTest, UserAddToGroupTest) {

        // arrange
        Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);
        Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
        std::string userPoolId = createdPoolList.front().userPoolId;
        Core::ExecResult createGroupResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-group --user-pool-id " + userPoolId + " --group-name " + GROUP_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createGroupResult.status);
        Core::ExecResult createUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-create-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserResult.status);

        // act
        Core::ExecResult addUserToGroupResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-add-user-to-group --user-pool-id " + userPoolId + " --group-name " + GROUP_NAME + " --username " + USER_NAME + " --endpoint " + _endpoint);
        Database::Entity::Cognito::UserList userList = _database.ListUsers();

        // assert
        EXPECT_EQ(0, addUserToGroupResult.status);
        EXPECT_EQ(1, userList.size());
        EXPECT_EQ(1, userList.front().groups.size());
        EXPECT_TRUE(userList.front().groups.front().groupName == GROUP_NAME);
    }

    TEST_F(CognitoServerCliTest, UserRemoveFromGroupTest) {

        // arrange
        Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);
        Database::Entity::Cognito::UserPoolList createdPoolList = _database.ListUserPools();
        std::string userPoolId = createdPoolList.front().userPoolId;
        Core::ExecResult createGroupResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-group --user-pool-id " + userPoolId + " --group-name " + GROUP_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createGroupResult.status);
        Core::ExecResult createUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-create-user --user-pool-id " + userPoolId + " --username " + USER_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserResult.status);
        Core::ExecResult addUserToGroupResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-add-user-to-group --user-pool-id " + userPoolId + " --group-name " + GROUP_NAME + " --username " + USER_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, addUserToGroupResult.status);

        // act
        Core::ExecResult removeUserFromGroupResult = Core::TestUtils::SendCliCommand("aws cognito-idp admin-remove-user-from-group --user-pool-id " + userPoolId + " --group-name " + GROUP_NAME + " --username " + USER_NAME + " --endpoint " + _endpoint);
        Database::Entity::Cognito::UserList userList = _database.ListUsers();

        // assert
        EXPECT_EQ(0, removeUserFromGroupResult.status);
        EXPECT_EQ(1, userList.size());
        EXPECT_EQ(0, userList.front().groups.size());
    }

    TEST_F(CognitoServerCliTest, UserSignUpTest) {

        // arrange
        Core::ExecResult createUserPoolResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool --pool-name " + USER_POOL_NAME + " --endpoint " + _endpoint);
        EXPECT_EQ(0, createUserPoolResult.status);
        Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();
        std::string userPoolId = userPoolList.front().userPoolId;
        Core::ExecResult createUserPoolClientResult = Core::TestUtils::SendCliCommand("aws cognito-idp create-user-pool-client --user-pool-id " + userPoolId + " --client-name " + CLIENT_NAME + " --endpoint " + _endpoint);
        userPoolList = _database.ListUserPools();
        std::string clientId = userPoolList.front().userPoolClients.front().clientId;

        // act
        Core::ExecResult signupUserResult = Core::TestUtils::SendCliCommand("aws cognito-idp sign-up --client-id " + clientId + " --username " + USER_NAME + " --password " + PASSWORD + " --endpoint " + _endpoint);
        Database::Entity::Cognito::UserList userList = _database.ListUsers();

        // assert
        EXPECT_EQ(0, signupUserResult.status);
        EXPECT_EQ(1, userList.size());
        EXPECT_TRUE(userList.front().enabled);
        EXPECT_TRUE(userList.front().userStatus == Database::Entity::Cognito::UserStatus::UNCONFIRMED);
    }

}// namespace AwsMock::Service

#endif// AWMOCK_COGNITO_SERVER_CLI_TEST_H