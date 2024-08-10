//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_COGNITO_SERVERJAVATEST_H
#define AWMOCK_COGNITO_SERVERJAVATEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/repository/CognitoDatabase.h>
#include <awsmock/service/cognito/CognitoServer.h>
#include <awsmock/service/gateway/GatewayServer.h>

#define REGION "eu-central-1"
#define TEST_USER_POOL "test-user-pool"
#define TEST_USER "test-user"
#define TEST_GROUP "test-group"
#define TEST_PORT 10100

namespace AwsMock::Service {

    class CognitoServerJavaTest : public ::testing::Test {

      protected:

        void SetUp() override {

            // Define endpoint
            _configuration.setInt("awsmock.service.gateway.http.port", TEST_PORT + 1);
            _configuration.setString("awsmock.service.gateway.http.host", "localhost");

            // Base URL
            _baseUrl = "/api/cognito/";

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(ioc);
            _gatewayServer->Initialize();
            _gatewayServer->Start();
        }

        void TearDown() override {
            _database.DeleteAllUsers();
            _database.DeleteAllGroups();
            _database.DeleteAllUserPools();
            _gatewayServer->Stop();
        }

        static Core::HttpSocketResponse SendGetCommand(const std::string &url, const std::string &payload) {
            std::map<std::string, std::string> headers;
            headers[to_string(http::field::content_type)] = "application/json";
            Core::HttpSocketResponse response = Core::HttpSocket::SendJson(http::verb::get, "localhost", TEST_PORT, url, payload, headers);
            log_debug << "Status: " << response.statusCode << " body: " << response.body;
            return response;
        }

        static Core::HttpSocketResponse SendPostCommand(const std::string &url, const std::string &payload) {
            std::map<std::string, std::string> headers;
            headers[to_string(http::field::content_type)] = "application/json";
            Core::HttpSocketResponse response = Core::HttpSocket::SendJson(http::verb::post, "localhost", TEST_PORT, url, payload, headers);
            log_debug << "Status: " << response.statusCode << " body: " << response.body;
            return response;
        }

        static Core::HttpSocketResponse SendDeleteCommand(const std::string &url, const std::string &payload) {
            std::map<std::string, std::string> headers;
            headers[to_string(http::field::content_type)] = "application/json";
            Core::HttpSocketResponse response = Core::HttpSocket::SendJson(http::verb::delete_, "localhost", TEST_PORT, url, payload, headers);
            log_debug << "Status: " << response.statusCode << " body: " << response.body;
            return response;
        }

        boost::asio::io_context ioc{10};
        std::string _endpoint, _baseUrl;
        Core::Configuration &_configuration = Core::Configuration::instance();
        Database::CognitoDatabase _database = Database::CognitoDatabase();
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
    };

    TEST_F(CognitoServerJavaTest, UserPoolCreateTest) {

        // arrange

        // act
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createUserPool?name=" + Core::StringUtils::UrlEncode(TEST_USER_POOL), {});
        Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_EQ(1, userPoolList.size());
    }

    TEST_F(CognitoServerJavaTest, UserPoolListTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createUserPool?name=" + Core::StringUtils::UrlEncode(TEST_USER_POOL), {});
        EXPECT_TRUE(result.statusCode == http::status::ok);
        Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();
        EXPECT_EQ(1, userPoolList.size());

        // act
        Core::HttpSocketResponse listResult = SendGetCommand(_baseUrl + "listUserPools?maxResults=10", {});
        EXPECT_TRUE(result.statusCode == http::status::ok);

        // assert
    }

    TEST_F(CognitoServerJavaTest, UserPoolDeleteTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createUserPool?name=" + Core::StringUtils::UrlEncode(TEST_USER_POOL), {});
        EXPECT_TRUE(result.statusCode == http::status::ok);
        Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();
        EXPECT_EQ(1, userPoolList.size());
        std::string userPoolId = userPoolList.front().userPoolId;

        // act
        Core::HttpSocketResponse deleteResult = SendDeleteCommand(_baseUrl + "deleteUserPool?userPoolId=" + Core::StringUtils::UrlEncode(userPoolId), {});
        long count = _database.CountUserPools();

        // assert
        EXPECT_TRUE(deleteResult.statusCode == http::status::ok);
        EXPECT_EQ(0, count);
    }

    TEST_F(CognitoServerJavaTest, UserCreateTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createUserPool?name=" + Core::StringUtils::UrlEncode(TEST_USER_POOL), {});
        EXPECT_TRUE(result.statusCode == http::status::ok);
        Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();
        EXPECT_EQ(1, userPoolList.size());
        std::string userPoolId = userPoolList.front().userPoolId;

        // act
        Core::HttpSocketResponse userCreateResult = SendPostCommand(_baseUrl + "createUser?userPoolId=" + Core::StringUtils::UrlEncode(userPoolId) + "&userName=" + Core::StringUtils::UrlEncode(TEST_USER), {});
        Database::Entity::Cognito::UserList userList = _database.ListUsers();

        // assert
        EXPECT_TRUE(userCreateResult.statusCode == http::status::ok);
        EXPECT_EQ(1, userList.size());
    }

    TEST_F(CognitoServerJavaTest, UserDeleteTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createUserPool?name=" + Core::StringUtils::UrlEncode(TEST_USER_POOL), {});
        EXPECT_TRUE(result.statusCode == http::status::ok);
        Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();
        EXPECT_EQ(1, userPoolList.size());
        std::string userPoolId = userPoolList.front().userPoolId;
        Core::HttpSocketResponse userCreateResult = SendPostCommand(_baseUrl + "createUser?userPoolId=" + Core::StringUtils::UrlEncode(userPoolId) + "&userName=" + Core::StringUtils::UrlEncode(TEST_USER), {});
        Database::Entity::Cognito::UserList userList = _database.ListUsers();
        EXPECT_EQ(1, userList.size());

        // act
        Core::HttpSocketResponse deleteResult = SendDeleteCommand(_baseUrl + "deleteUser?userPoolId=" + Core::StringUtils::UrlEncode(userPoolId) + "&userName=" + Core::StringUtils::UrlEncode(TEST_USER), {});
        long count = _database.CountUsers();

        // assert
        EXPECT_TRUE(deleteResult.statusCode == http::status::ok);
        EXPECT_EQ(0, count);
    }

    TEST_F(CognitoServerJavaTest, GroupCreateTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createUserPool?name=" + Core::StringUtils::UrlEncode(TEST_USER_POOL), {});
        EXPECT_TRUE(result.statusCode == http::status::ok);
        Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();
        EXPECT_EQ(1, userPoolList.size());
        std::string userPoolId = userPoolList.front().userPoolId;

        // act
        Core::HttpSocketResponse userCreateResult = SendPostCommand(_baseUrl + "createUserGroup?userPoolId=" + Core::StringUtils::UrlEncode(userPoolId) + "&groupName=" + Core::StringUtils::UrlEncode(TEST_GROUP), {});
        Database::Entity::Cognito::GroupList groupList = _database.ListGroups();

        // assert
        EXPECT_TRUE(userCreateResult.statusCode == http::status::ok);
        EXPECT_EQ(1, groupList.size());
    }

    TEST_F(CognitoServerJavaTest, GroupDeleteTest) {

        // arrange
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createUserPool?name=" + Core::StringUtils::UrlEncode(TEST_USER_POOL), {});
        EXPECT_TRUE(result.statusCode == http::status::ok);
        Database::Entity::Cognito::UserPoolList userPoolList = _database.ListUserPools();
        EXPECT_EQ(1, userPoolList.size());
        std::string userPoolId = userPoolList.front().userPoolId;
        Core::HttpSocketResponse userCreateResult = SendPostCommand(_baseUrl + "createUserGroup?userPoolId=" + Core::StringUtils::UrlEncode(userPoolId) + "&groupName=" + Core::StringUtils::UrlEncode(TEST_GROUP), {});
        Database::Entity::Cognito::GroupList userGroupList = _database.ListGroups();
        EXPECT_EQ(1, userGroupList.size());

        // act
        Core::HttpSocketResponse deleteDeleteResult = SendDeleteCommand(_baseUrl + "deleteUserGroup?userPoolId=" + Core::StringUtils::UrlEncode(userPoolId) + "&groupName=" + Core::StringUtils::UrlEncode(TEST_GROUP), {});
        userGroupList = _database.ListGroups();

        // assert
        EXPECT_TRUE(userCreateResult.statusCode == http::status::ok);
        EXPECT_EQ(0, userGroupList.size());
    }

}// namespace AwsMock::Service

#endif// AWMOCK_COGNITO_SERVERJAVATEST_H