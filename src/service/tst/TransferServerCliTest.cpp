//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_SERVICE_TRANSFER_SERVER_CLI_TEST_H
#define AWMOCK_SERVICE_TRANSFER_SERVER_CLI_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/FileUtils.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/gateway/GatewayServer.h>
#include <awsmock/service/s3/S3Server.h>

// Test includes
#include "TestBase.h"
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define TEST_BUCKET_NAME std::string("test-bucket")
#define TEST_BUCKET std::string("s3://test-bucket")
#define S3_ACCOUNT_ID "000000000000"

namespace AwsMock::Service {

    class TransferServerCliTest : public ::testing::Test, public TestBase {

      protected:

        void SetUp() override {
            StartGateway();
        }

        void TearDown() override {
            _database.DeleteAllTransfers();
        }
        Database::TransferDatabase &_database = Database::TransferDatabase::instance();
    };

    TEST_F(TransferServerCliTest, TransferServerEmptyListTest) {

        // arrange

        // act
        auto [status, output] = Core::TestUtils::SendCliCommand("aws transfer list-servers --endpoint " + GetEndpoint());
        const Database::Entity::Transfer::TransferList transferList = _database.ListServers();

        // assert
        EXPECT_EQ(0, status);
        EXPECT_EQ(0, transferList.size());
    }

    TEST_F(TransferServerCliTest, TransferServerListTest) {

        // arrange
        auto [status1, output1] = Core::TestUtils::SendCliCommand("aws transfer create-server --protocols ftp --endpoint " + GetEndpoint());
        Database::Entity::Transfer::TransferList transferList = _database.ListServers();
        EXPECT_EQ(0, status1);
        EXPECT_EQ(1, transferList.size());

        // act
        auto [status2, output2] = Core::TestUtils::SendCliCommand("aws transfer list-servers --endpoint " + GetEndpoint());
        transferList = _database.ListServers();

        // assert
        EXPECT_EQ(0, status2);
        EXPECT_EQ(1, transferList.size());
    }

    TEST_F(TransferServerCliTest, TransferServerCreateTest) {

        // arrange

        // act
        auto [status, output] = Core::TestUtils::SendCliCommand("aws transfer create-server --protocols ftp --endpoint " + GetEndpoint());
        const Database::Entity::Transfer::TransferList transferList = _database.ListServers();

        // assert
        EXPECT_EQ(0, status);
        EXPECT_EQ(1, transferList.size());
        EXPECT_FALSE(transferList.front().serverId.empty());
        EXPECT_TRUE(Core::StringUtils::Contains(output, "ServerId"));
    }

    TEST_F(TransferServerCliTest, TransferServerDeleteTest) {

        // arrange
        auto [status1, output1] = Core::TestUtils::SendCliCommand("aws transfer create-server --protocols ftp --endpoint " + GetEndpoint());
        Database::Entity::Transfer::TransferList transferList = _database.ListServers();
        EXPECT_EQ(0, status1);
        const std::string serverId = transferList.front().serverId;

        // act
        auto [status2, output2] = Core::TestUtils::SendCliCommand("aws transfer delete-server --server-id " + serverId + " --endpoint " + GetEndpoint());
        transferList = _database.ListServers();

        // assert
        EXPECT_EQ(0, status2);
        EXPECT_EQ(0, transferList.size());
    }

}// namespace AwsMock::Service

#endif// AWMOCK_SERVICE_S3_SERVER_CLI_TEST_H