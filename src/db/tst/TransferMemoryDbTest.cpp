//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_TRANSFERMEMORYDBTEST_H
#define AWMOCK_CORE_TRANSFERMEMORYDBTEST_H

// C++ standard includes
#include <iostream>
#include <vector>

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/TransferDatabase.h>

// MongoDB includes
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/client.hpp>

#define BUCKET "test-bucket"
#define OWNER "test-owner"

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  class TransferMemoryDbTest : public ::testing::Test {

  protected:

    void SetUp() override {
      _region = _configuration.getString("awsmock.region");
    }

    void TearDown() override {
      _transferDatabase.DeleteAllTransfers();
    }

    std::string _region;
    Core::Configuration& _configuration = Core::TestUtils::GetTestConfiguration(false);
    TransferDatabase& _transferDatabase = TransferDatabase::instance();
  };

  TEST_F(TransferMemoryDbTest, TransferCreateTest) {

    // arrange
    Entity::Transfer::Transfer transfer = {.region=_region, .protocols={"tcp", "ftp"}};

    // act
    Entity::Transfer::Transfer result = _transferDatabase.CreateTransfer(transfer);

    // assert
    EXPECT_TRUE(result.protocols[0] == "tcp");
    EXPECT_TRUE(result.region == _region);
  }

  TEST_F(TransferMemoryDbTest, TransferExistsUniqueTest) {

    // arrange
    Entity::Transfer::Transfer transfer1 = {.region=_region, .protocols={"tcp", "ftp"}};
    Entity::Transfer::Transfer transfer2 = {.region=_region, .protocols={"tcp", "http"}};
    transfer1 = _transferDatabase.CreateTransfer(transfer1);

    // act
    bool result1 = _transferDatabase.TransferExists(_region, transfer1.protocols);
    bool result2 = _transferDatabase.TransferExists(_region, transfer2.protocols);

    // assert
    EXPECT_TRUE(result1);
    EXPECT_FALSE(result2);
  }

  TEST_F(TransferMemoryDbTest, TransferExistsByServerIdTest) {

    // arrange
    Entity::Transfer::Transfer transfer = {.region=_region, .protocols={"tcp", "ftp"}};
    transfer = _transferDatabase.CreateTransfer(transfer);

    // act
    bool result1 = _transferDatabase.TransferExists(_region, transfer.serverId);
    bool result2 = _transferDatabase.TransferExists(transfer.serverId);

    // assert
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
  }

  TEST_F(TransferMemoryDbTest, TransferGetByServerIdTest) {

    // arrange
    Entity::Transfer::Transfer transfer = {.region=_region, .serverId="test", .protocols={"tcp", "ftp"}};
    transfer = _transferDatabase.CreateTransfer(transfer);

    // act
    Entity::Transfer::Transfer result = _transferDatabase.GetTransferByServerId(transfer.serverId);

    // assert
    EXPECT_TRUE(result.serverId == transfer.serverId);
  }

  TEST_F(TransferMemoryDbTest, TransferGetByServerArnTest) {

    // arrange
    Entity::Transfer::Transfer transfer = {.region=_region, .arn="aws:transfer", .protocols={"tcp", "ftp"}};
    transfer = _transferDatabase.CreateTransfer(transfer);

    // act
    Entity::Transfer::Transfer result = _transferDatabase.GetTransferByArn(transfer.arn);

    // assert
    EXPECT_TRUE(result.arn == transfer.arn);
  }

  TEST_F(TransferMemoryDbTest, TransferUpdateTest) {

    // arrange
    Entity::Transfer::Transfer transfer = {.region=_region, .protocols={"tcp", "ftp"}};
    transfer = _transferDatabase.CreateTransfer(transfer);

    // act
    transfer.users.push_back({.userName="test", .password="test", .homeDirectory="/"});
    Entity::Transfer::Transfer result = _transferDatabase.UpdateTransfer(transfer);

    // assert
    EXPECT_TRUE(result.users[0].userName == "test");
  }

  TEST_F(TransferMemoryDbTest, TransferDeleteTest) {

    // arrange
    Entity::Transfer::Transfer transfer = {.region=_region, .protocols={"tcp", "ftp"}};
    transfer = _transferDatabase.CreateTransfer(transfer);

    // act
    _transferDatabase.DeleteTransfer(transfer.serverId);
    bool result = _transferDatabase.TransferExists(transfer.serverId);

    // assert
    EXPECT_FALSE(result);
  }

  TEST_F(TransferMemoryDbTest, TransferDeleteAllTest) {

    // arrange
    Entity::Transfer::Transfer transfer1 = {.region=_region, .protocols={"tcp", "ftp"}};
    Entity::Transfer::Transfer transfer2 = {.region=_region, .protocols={"tcp", "ftp"}};
    transfer1 = _transferDatabase.CreateTransfer(transfer1);
    transfer2 = _transferDatabase.CreateTransfer(transfer2);

    // act
    _transferDatabase.DeleteAllTransfers();
    bool result1 = _transferDatabase.TransferExists(transfer1.serverId);
    bool result2 = _transferDatabase.TransferExists(transfer2.serverId);

    // assert
    EXPECT_FALSE(result1);
    EXPECT_FALSE(result2);
  }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_TRANSFERMEMORYDBTEST_H