//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_SERVICE_S3_SERVER_JAVA_TEST_H
#define AWMOCK_SERVICE_S3_SERVER_JAVA_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/repository/S3Database.h>
#include "awsmock/service/s3/S3Server.h"

// Test includes
#include <awsmock/core/TestUtils.h>

#define REGION "eu-central-1"
#define BUCKET "test-bucket"
#define KEY "testfile.json"
#define OWNER "test-owner"

namespace AwsMock::Service {

  class S3ServerJavaTest : public ::testing::Test {

    protected:

    void SetUp() override {

      // Define endpoint
      std::string _port = _configuration.getString("awsmock.service.s3.port", std::to_string(S3_DEFAULT_PORT));
      std::string _host = _configuration.getString("awsmock.service.s3.host", S3_DEFAULT_HOST);
      _endpoint = "http://" + _host + ":" + _port;

      // Set base command
      _baseCommand = "java -jar /usr/local/lib/awsmock-java-test-0.0.1-SNAPSHOT-jar-with-dependencies.jar " + _endpoint;

      // Temporary file
      _tempFile = Core::FileUtils::CreateTempFile("txt");

      // Start HTTP manager
      _s3Server.Start();
    }

    void TearDown() override {
      Core::FileUtils::DeleteFile(_tempFile);
      _database.DeleteAllObjects();
      _database.DeleteAllBuckets();
    }

    std::string _endpoint, _baseCommand, _tempFile;
    std::map<std::string, std::string> _extraHeaders;
    Core::Configuration& _configuration = Core::Configuration::instance();
    Core::MetricService& _metricService = Core::MetricService::instance();
    Database::S3Database _database = Database::S3Database();
    S3Server _s3Server = S3Server(_configuration, _metricService);
  };

  TEST_F(S3ServerJavaTest, BucketCreateTest) {

    // arrange

    // act
    Core::ExecResult result = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();

    // assert
    EXPECT_EQ(0, result.status);
    EXPECT_EQ(1, bucketList.size());
  }

  TEST_F(S3ServerJavaTest, BucketListTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult listResult = Core::SystemUtils::Exec(_baseCommand + " s3 list-bucket test-bucket");
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();

    // assert
    EXPECT_EQ(0, listResult.status);
    EXPECT_TRUE(Core::StringUtils::Contains(listResult.output, "test-bucket"));
    EXPECT_EQ(1, bucketList.size());
  }

  TEST_F(S3ServerJavaTest, BucketDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult deleteResult = Core::SystemUtils::Exec(_baseCommand + " s3 delete-bucket test-bucket");
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();

    // assert
    EXPECT_EQ(0, deleteResult.status);
    EXPECT_EQ(0, bucketList.size());
  }

  TEST_F(S3ServerJavaTest, ObjectPutTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket " + BUCKET);
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult putResult = Core::SystemUtils::Exec(_baseCommand + " s3 put-object " + BUCKET + " test-key \"test-object\"");
    EXPECT_EQ(0, putResult.status);
    Database::Entity::S3::ObjectList objectList = _database.ListBucket(BUCKET);

    // assert
    EXPECT_EQ(1, objectList.size());
  }

  TEST_F(S3ServerJavaTest, ObjectGetTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult putResult = Core::SystemUtils::Exec(_baseCommand + " s3 put-object " + BUCKET + " test-key \"test-object\"");
    EXPECT_EQ(0, putResult.status);

    // act
    Core::ExecResult getResult = Core::SystemUtils::Exec(_baseCommand + " s3 get-object " + BUCKET + " test-key " + _tempFile);
    EXPECT_EQ(0, getResult.status);

    // assert
    EXPECT_EQ(0, getResult.status);
    EXPECT_TRUE(Core::FileUtils::FileSize(_tempFile) > 0);
  }

  TEST_F(S3ServerJavaTest, ObjectCopyTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult putResult = Core::SystemUtils::Exec(_baseCommand + " s3 put-object " + BUCKET + " test-key \"test-object\"");
    EXPECT_EQ(0, putResult.status);

    // act
    Core::ExecResult copyResult = Core::SystemUtils::Exec(_baseCommand + " s3 copy-object " + BUCKET + " test-key " + BUCKET + " test-key1");
    EXPECT_EQ(0, copyResult.status);
    Core::ExecResult getResult = Core::SystemUtils::Exec(_baseCommand + " s3 get-object " + BUCKET + " test-key1 " + _tempFile);
    EXPECT_EQ(0, getResult.status);

    // assert
    EXPECT_EQ(0, getResult.status);
    EXPECT_TRUE(Core::FileUtils::FileSize(_tempFile) > 0);
  }

  TEST_F(S3ServerJavaTest, ObjectDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult putResult = Core::SystemUtils::Exec(_baseCommand + " s3 put-object test-bucket test-key \"test-object\"");
    EXPECT_EQ(0, putResult.status);

    // act
    Core::ExecResult deleteResult = Core::SystemUtils::Exec(_baseCommand + " s3 delete-object test-bucket test-key");
    long count = _database.ObjectCount();

    // assert
    EXPECT_EQ(0, deleteResult.status);
    EXPECT_EQ(0, count);
  }

  // Java client tries to upload a 10 MB file.
  TEST_F(S3ServerJavaTest, ObjectsUpdloadBigFileTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult uploadResult = Core::SystemUtils::Exec(_baseCommand + " s3 upload-big-object test-bucket test-key 10");
    long count = _database.ObjectCount();

    // assert
    EXPECT_EQ(0, uploadResult.status);
    EXPECT_EQ(1, count);
  }

  // Java client tries to download a 10 MB file.
  TEST_F(S3ServerJavaTest, ObjectsDownloadBigFileTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult uploadResult = Core::SystemUtils::Exec(_baseCommand + " s3 upload-big-object test-bucket test-key 10");
    EXPECT_EQ(0, uploadResult.status);

    // act
    Core::ExecResult downloadResult = Core::SystemUtils::Exec(_baseCommand + " s3 download-big-object test-bucket test-key");
    long count = _database.ObjectCount();

    // assert
    EXPECT_EQ(0, downloadResult.status);
    EXPECT_EQ(1, count);
  }

  // Java client tries to get the file size.
  TEST_F(S3ServerJavaTest, ObjectGetSizeTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult uploadResult = Core::SystemUtils::Exec(_baseCommand + " s3 upload-big-object test-bucket test-key 10");
    EXPECT_EQ(0, uploadResult.status);

    // act
    Core::ExecResult headResult = Core::SystemUtils::Exec(_baseCommand + " s3 head-object test-bucket test-key");

    // assert
    EXPECT_EQ(0, headResult.status);
    EXPECT_TRUE(Core::StringUtils::ContainsIgnoreCase(headResult.output, "ContentLength=10485852"));
  }

  // Java client tries to get the file size.
  TEST_F(S3ServerJavaTest, ObjectVersionListTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult putResult = Core::SystemUtils::Exec(_baseCommand + " s3 put-object test-bucket test-key \"test-object\"");
    EXPECT_EQ(0, putResult.status);

    // act
    Core::ExecResult listVersionsResult = Core::SystemUtils::Exec(_baseCommand + " s3 list-versions test-bucket test-key");

    // assert
    EXPECT_EQ(0, listVersionsResult.status);
    //EXPECT_TRUE(Core::StringUtils::ContainsIgnoreCase(headResult.output, "ContentLength=10485852"));
  }

  TEST_F(S3ServerJavaTest, ObjectsDeleteTest) {

    // arrange
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);
    Core::ExecResult putResult1 = Core::SystemUtils::Exec(_baseCommand + " s3 put-object test-bucket test-key1 \"test-object\"");
    EXPECT_EQ(0, putResult1.status);
    Core::ExecResult putResult2 = Core::SystemUtils::Exec(_baseCommand + " s3 put-object test-bucket test-key2 \"test-object\"");
    EXPECT_EQ(0, putResult2.status);

    // act
    Core::ExecResult deleteResult = Core::SystemUtils::Exec(_baseCommand + " s3 delete-objects test-bucket test-key1 test-key2");
    EXPECT_EQ(0, deleteResult.status);
    long count = _database.ObjectCount();

    // assert
    EXPECT_EQ(0, deleteResult.status);
    EXPECT_EQ(0, count);
  }

} // namespace AwsMock::Core

#endif // AWMOCK_SERVICE_S3_SERVER_JAVA_TEST_H