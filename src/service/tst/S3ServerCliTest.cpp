//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_S3_S3SERVERCLITEST_H
#define AWMOCK_S3_S3SERVERCLITEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/S3Server.h>
#include <awsmock/service/S3Service.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define OWNER "test-owner"
#define TEST_BUCKET_NAME std::string("test-bucket")
#define TEST_BUCKET std::string("s3://test-bucket")
#define S3_ACCOUNT_ID "000000000000"

namespace AwsMock::Service {

  class S3ServerCliTest : public ::testing::Test {

  protected:

    void SetUp() override {

      // Define endpoint
      std::string _port = _configuration.getString("awsmock.service.s3.port", std::to_string(S3_DEFAULT_PORT));
      std::string _host = _configuration.getString("awsmock.service.s3.host", S3_DEFAULT_HOST);
      _configuration.setString("awsmock.service.gateway.port", _port);
      _accountId = _configuration.getString("awsmock.account.id", S3_ACCOUNT_ID);
      _endpoint = "http://" + _host + ":" + _port;

      // Start HTTP manager
      Poco::ThreadPool::defaultPool().start(_s3Server);
    }

    void TearDown() override {
      _database.DeleteAllObjects();
      _database.DeleteAllBuckets();
      _s3Server.StopServer();
    }

    std::string _endpoint, _accountId;
    Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration();
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::S3Database _database = Database::S3Database(_configuration);
    S3Server _s3Server = S3Server(_configuration, _metricService);
  };

  TEST_F(S3ServerCliTest, BucketCreateTest) {

    // arrange

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("sqs", "aws s3 mb " + TEST_BUCKET + " --endpoint " + _endpoint);
    EXPECT_EQ(0, result.status);
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(1, bucketList.size());
  }

  TEST_F(S3ServerCliTest, BucketListTest) {

    // arrange
    std::string filename = Core::FileUtils::CreateTempFile("json", 10);
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 mb " + TEST_BUCKET + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("sqs", "aws s3 ls --endpoint " + _endpoint);

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_TRUE(result.output.length() > 0);
    EXPECT_TRUE(Core::StringUtils::Contains(result.output, TEST_BUCKET_NAME));
  }

  TEST_F(S3ServerCliTest, BucketDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 mb " + TEST_BUCKET + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("sqs", "aws s3 rb " + TEST_BUCKET + " --endpoint " + _endpoint);
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(0, bucketList.size());
  }

  TEST_F(S3ServerCliTest, ObjectCreateTest) {

    // arrange
    std::string filename = Core::FileUtils::CreateTempFile("json", 10);
    Core::ExecResult createResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 mb " + TEST_BUCKET + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("sqs", "aws s3 cp " + filename + " " + TEST_BUCKET + "/" + filename + " --endpoint " + _endpoint);
    Database::Entity::S3::ObjectList objectList = _database.ListBucket("test-bucket");

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(1, objectList.size());
  }

  TEST_F(S3ServerCliTest, ObjectGetTest) {

    // arrange
    std::string filename = Core::FileUtils::CreateTempFile("json", 10);
    Core::ExecResult createBucketResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 mb " + TEST_BUCKET + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createBucketResult.status);
    Core::ExecResult createObjectResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 cp " + filename + " " + TEST_BUCKET + "/" + filename + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createObjectResult.status);

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("sqs", "aws s3 cp " + TEST_BUCKET + "/" + filename + " " + filename + " --endpoint " + _endpoint);

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(10, Core::FileUtils::FileSize(filename));
    EXPECT_TRUE(Core::FileUtils::FileExists(filename));
  }

  TEST_F(S3ServerCliTest, ObjectCopyTest) {

    // arrange
    std::string filename = Core::FileUtils::CreateTempFile("json", 10);
    Core::ExecResult createBucketResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 mb " + TEST_BUCKET + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createBucketResult.status);
    Core::ExecResult createObjectResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 cp " + filename + " " + TEST_BUCKET + "/" + filename + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createObjectResult.status);

    // act
    Core::ExecResult copyResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 cp " + TEST_BUCKET + "/" + filename + " " + TEST_BUCKET + "/test/" + filename + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createObjectResult.status);
    Database::Entity::S3::ObjectList objectList = _database.ListBucket(TEST_BUCKET_NAME);

    // assert
    EXPECT_EQ(2, objectList.size());
    EXPECT_TRUE(objectList[0].key == filename);
    EXPECT_TRUE(objectList[1].key == "test/" + filename);
  }

  TEST_F(S3ServerCliTest, ObjectMoveTest) {

    // arrange
    std::string filename = Core::FileUtils::CreateTempFile("json", 10);
    Core::ExecResult createBucketResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 mb " + TEST_BUCKET + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createBucketResult.status);
    Core::ExecResult createObjectResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 cp " + filename + " " + TEST_BUCKET + "/" + filename + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createObjectResult.status);

    // act
    Core::ExecResult copyResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 mv " + TEST_BUCKET + "/" + filename + " " + TEST_BUCKET + "/test/" + filename + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createObjectResult.status);
    Database::Entity::S3::ObjectList objectList = _database.ListBucket(TEST_BUCKET_NAME);

    // assert
    EXPECT_EQ(1, objectList.size());
    EXPECT_TRUE(objectList[0].key == "test/" + filename);
  }

  TEST_F(S3ServerCliTest, ObjectDeleteTest) {

    // arrange
    std::string filename = Core::FileUtils::CreateTempFile("json", 10);
    Core::ExecResult createBucketResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 mb " + TEST_BUCKET + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createBucketResult.status);
    Core::ExecResult createObjectResult = Core::TestUtils::SendCliCommand("sqs", "aws s3 cp " + filename + " " + TEST_BUCKET + "/" + filename + " --endpoint " + _endpoint);
    EXPECT_EQ(0, createObjectResult.status);

    // act
    Core::ExecResult result = Core::TestUtils::SendCliCommand("sqs", "aws s3 rm " + TEST_BUCKET + "/" + filename + " --endpoint " + _endpoint);
    Database::Entity::S3::ObjectList objectList = _database.ListBucket("test-bucket");

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(0, objectList.size());
  }

} // namespace AwsMock::Service

#endif // AWMOCK_S3_S3SERVERCLITEST_H