//
// Created by vogje01 on 12/18/23.
//

#ifndef AWMOCK_DTO_TRANSFER_CREATE_USER_REQUEST_TEST_H
#define AWMOCK_DTO_TRANSFER_CREATE_USER_REQUEST_TEST_H

// C++ includes
#include <sstream>
#include <string>

// GTest includes
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/dto/transfer/CreateUserRequest.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define CREATE_USER_REQUEST_TO_STRING "CreateUserRequest={\"HomeDirectory\":\"test-user\",\"Password\":\"password\",\"Region\":\"eu-central-1\",\"ServerId\":\"test-server_id\",\"UserName\":\"test-user\"}"
#define CREATE_USER_REQUEST_TO_JSON "{\"HomeDirectory\":\"test-user\",\"Password\":\"password\",\"Region\":\"eu-central-1\",\"ServerId\":\"test-server_id\",\"UserName\":\"test-user\"}"
#define CREATE_USER_REQUEST_FROM_JSON "{\"HomeDirectory\":\"test-user\",\"Password\":\"password\",\"Region\":\"eu-central-1\",\"ServerId\":\"test-server_id\",\"UserName\":\"test-user\"}"

namespace AwsMock::Dto::Transfer {

    class CreateUserRequestTest : public ::testing::Test {
      protected:

        void SetUp() override {
            // General configuration
            _region = _configuration.getString("awsmock.region", "eu-central-1");
        }

        void TearDown() override {
        }

        std::string _region;
        Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
    };

    TEST_F(CreateUserRequestTest, ToStringTest) {

        // arrange
        Dto::Transfer::CreateUserRequest createRequest = {.region = _region, .serverId = "test-server_id", .userName = "test-user", .password = "password", .homeDirectory = "test-user"};

        // act
        std::string stringRepresentation = createRequest.ToString();

        // assert
        EXPECT_FALSE(stringRepresentation.empty());
        EXPECT_STREQ(stringRepresentation.c_str(), CREATE_USER_REQUEST_TO_STRING);
    }

    TEST_F(CreateUserRequestTest, ToJsonTest) {

        // arrange
        Dto::Transfer::CreateUserRequest createRequest = {.region = _region, .serverId = "test-server_id", .userName = "test-user", .password = "password", .homeDirectory = "test-user"};

        // act
        std::string jsonRepresentation = createRequest.ToJson();

        // assert
        EXPECT_FALSE(jsonRepresentation.empty());
        EXPECT_STREQ(jsonRepresentation.c_str(), CREATE_USER_REQUEST_TO_JSON);
    }

    TEST_F(CreateUserRequestTest, FromJsonTest) {

        // arrange
        Dto::Transfer::CreateUserRequest createRequest;
        std::string jsonRepresentation = CREATE_USER_REQUEST_FROM_JSON;

        // act
        createRequest.FromJson(jsonRepresentation);

        // assert
        EXPECT_TRUE(createRequest.region == _region);
        EXPECT_TRUE(createRequest.serverId == "test-server_id");
        ASSERT_THAT(createRequest.userName, "test-user");
    }
}// namespace AwsMock::Dto::Transfer

#endif// AWMOCK_DTO_TRANSFER_CREATE_USER_REQUEST_TEST_H
