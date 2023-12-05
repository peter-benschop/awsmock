//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_S3SERVERTEST_H
#define AWMOCK_CORE_S3SERVERTEST_H

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
#define BUCKET "test-bucket"
#define KEY "testfile.json"
#define OWNER "test-owner"
#define LOCATION_CONSTRAINT "<CreateBucketConfiguration xmlns=\"http://s3.amazonaws.com/doc/2006-03-01/\"> \
                                <LocationConstraint>eu-central-1</LocationConstraint> \
                             </CreateBucketConfiguration>"
#define CREATE_BUCKET_RESPONSE "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<CreateBucketResult>\n\t<BucketArn>arn</BucketArn>\n</CreateBucketResult>\n"
#define TEST_CONTENT R"({"test":"test"})"
#define VERSIONING_BODY "<VersioningConfiguration xmlns=\"http://s3.amazonaws.com/doc/2006-03-01/\">" \
                        "  <Status>Enabled</Status>" \
                        "</VersioningConfiguration>"

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

      // Start HTTP manager
      Poco::ThreadPool::defaultPool().addCapacity(10);
      Poco::ThreadPool::defaultPool().start(_s3Server);
    }

    void TearDown() override {
      _database.DeleteAllObjects();
      _database.DeleteAllBuckets();
      _s3Server.StopServer();
    }

    Core::CurlUtils _curlUtils;
    std::string _endpoint, _baseCommand;
    std::map<std::string, std::string> _extraHeaders;
    Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration();
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::S3Database _database = Database::S3Database(_configuration);
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

  /*TEST_F(S3ServerJavaTest, BucketCreateVersionedTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetCliUserAgentHeader("s3", "mb");
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();
    EXPECT_EQ(1, bucketList.size());

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetCliUserAgentHeader("s3", "cp");
    Core::CurlResponse versioningResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "?versioning", _extraHeaders, VERSIONING_BODY);

    // assert
    EXPECT_TRUE(versioningResponse.statusCode == Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    EXPECT_EQ(1, bucketList.size());
  }*/

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
    Core::ExecResult createResult = Core::SystemUtils::Exec(_baseCommand + " s3 create-bucket test-bucket");
    EXPECT_EQ(0, createResult.status);

    // act
    Core::ExecResult putResult = Core::SystemUtils::Exec(_baseCommand + " s3 put-object test-bucket test-key \"test-object\"");
    Database::Entity::S3::ObjectList objectList = _database.ListBucket(BUCKET);

    // assert
    //EXPECT_EQ(0, putResult.status);
    EXPECT_EQ(1, objectList.size());
  }

  /*TEST_F(S3ServerJavaTest, ObjectGetTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetCliUserAgentHeader("s3", "mb");
    Core::CurlResponse bucketCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    EXPECT_TRUE(bucketCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetCliUserAgentHeader("s3", "cp");
    Core::CurlResponse objectCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders, TEST_CONTENT);
    EXPECT_TRUE(objectCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetCliUserAgentHeader("s3", "cp");
    Core::CurlResponse objectGetResponse = _curlUtils.SendHttpRequest("GET", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders);

    // assert
    EXPECT_TRUE(objectGetResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_FALSE(objectGetResponse.output.empty());
  }

  TEST_F(S3ServerJavaTest, ObjectDeleteTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetCliUserAgentHeader("s3", "mb");
    Core::CurlResponse bucketCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    EXPECT_TRUE(bucketCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetCliUserAgentHeader("s3", "cp");
    Core::CurlResponse objectCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders, TEST_CONTENT);
    EXPECT_TRUE(objectCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetCliUserAgentHeader("s3", "rm");
    Core::CurlResponse objectDeleteResponse = _curlUtils.SendHttpRequest("DELETE", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders);
    Database::Entity::S3::ObjectList objectList = _database.ListBucket(BUCKET);

    // assert
    EXPECT_TRUE(objectDeleteResponse.statusCode == Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    EXPECT_EQ(0, objectList.size());
  }*/

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_S3SERVERTEST_H