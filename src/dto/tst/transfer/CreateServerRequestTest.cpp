//
// Created by vogje01 on 12/18/23.
//

#ifndef AWMOCK_DTO_TRANSFER_CREATE_SERVER_REQUEST_TEST_H
#define AWMOCK_DTO_TRANSFER_CREATE_SERVER_REQUEST_TEST_H

// GTest includes
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/dto/transfer/CreateServerRequest.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define CREATE_SERVER_REQUEST_TO_STRING "CreateServerRequest={region='eu-central-1', tags=[Tag={key='version', value='1.0'}], protocols=['ftp', 'sftp']}"
#define CREATE_SERVER_REQUEST_TO_JSON "{\"Domain\":\"test.com\",\"Region\":\"eu-central-1\"}"
#define CREATE_SERVER_REQUEST_FROM_JSON "{\"Domain\":\"test.com\",\"Region\":\"eu-central-1\", \"Protocols\":[\"ftp\", \"sftp\"], \"tags\":[{\"key\":\"value\"}]}"

namespace AwsMock::Dto::Transfer {

    class CreateServerRequestTest : public ::testing::Test {
      protected:

        void SetUp() override {
            // General configuration
            _region = _configuration.getString("awsmock.region", "eu-central-1");
        }

        void TearDown() override {
        }

        std::string _region;
        std::vector<std::string> _protocols = {"ftp", "sftp"};
        Dto::Transfer::IdentityProviderDetails _identityProviderDetails = {.directoryId = "directoryId", .function = "function", .invocationRole = "invocationRole", .sftpAuthenticationMethods = "sftpAuthenticationMethods", .url = "url"};
        std::vector<Dto::Transfer::Tag> _tags = {{.key = "version", .value = "1.0"}};
        Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
    };

    TEST_F(CreateServerRequestTest, ToStringTest) {

        // arrange
        Dto::Transfer::CreateServerRequest createRequest = {.region = _region, .domain = "test.com", .protocols = _protocols, .tags = _tags, .identityProviderDetails = _identityProviderDetails};

        // act
        std::string stringRepresentation = createRequest.ToString();

        // assert
        EXPECT_FALSE(stringRepresentation.empty());
        EXPECT_TRUE(Core::StringUtils::Equals(stringRepresentation, CREATE_SERVER_REQUEST_TO_STRING));
    }

    TEST_F(CreateServerRequestTest, ToJsonTest) {

        // arrange
        Dto::Transfer::CreateServerRequest createRequest = {.region = _region, .domain = "test.com", .protocols = _protocols, .tags = _tags, .identityProviderDetails = _identityProviderDetails};

        // act
        std::string jsonRepresentation = createRequest.ToJson();

        // assert
        EXPECT_FALSE(jsonRepresentation.empty());
        EXPECT_TRUE(Core::StringUtils::Equals(jsonRepresentation, CREATE_SERVER_REQUEST_TO_JSON));
    }

    TEST_F(CreateServerRequestTest, FromJsonTest) {

        // arrange
        Dto::Transfer::CreateServerRequest createRequest;
        std::string jsonRepresentation = CREATE_SERVER_REQUEST_FROM_JSON;

        // act
        createRequest.FromJson(jsonRepresentation);

        // assert
        EXPECT_TRUE(createRequest.region == _region);
        EXPECT_TRUE(createRequest.domain == "test.com");
        //    ASSERT_THAT(createRequest.protocols, testing::ElementsAre("ftp", "sftp"));
        for (const auto &it: createRequest.tags) {
            EXPECT_TRUE(it.key == "key");
            EXPECT_TRUE(it.value == "value");
        }
    }
}// namespace AwsMock::Dto::Transfer

#endif// AWMOCK_DTO_TRANSFER_CREATE_SERVER_REQUEST_TEST_H
