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
#define CREATE_BUCKET_RESPONSE "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<CreateBucketResult>\n\t<BuckerArn>arn</BuckerArn>\n</CreateBucketResult>\n"
#define TEST_CONTENT R"({"test":"test"})"
#define VERSIONING_BODY "<VersioningConfiguration xmlns=\"http://s3.amazonaws.com/doc/2006-03-01/\">" \
                        "  <Status>Enabled</Status>" \
                        "</VersioningConfiguration>"

namespace AwsMock::Service {

  class S3ServerTest : public ::testing::Test {

    protected:

    void SetUp() override {
      // Set log level
      Core::LogStream::SetGlobalLevel("error");

      // Create some test objects
      _testFile = Core::FileUtils::CreateTempFile("/tmp", "json", 10);
      _extraHeaders["Authorization"] =
        "AWS4-HMAC-SHA256 Credential=none/20230618/eu-central-1/s3/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840";

      // Define endpoint
      std::string _port = _configuration.getString("awsmock.module.s3.port", std::to_string(S3_DEFAULT_PORT));
      std::string _host = _configuration.getString("awsmock.module.s3.host", S3_DEFAULT_HOST);
      _endpoint = "http://" + _host + ":" + _port;

      // Start HTTP manager
      Poco::ThreadPool::defaultPool().start(_s3Server);
      while(!_s3Server.IsRunning()) {
        Poco::Thread::sleep(1000);
      }
    }

    void TearDown() override {
      _s3Server.StopServer();
      _database.DeleteAllBuckets();
      Core::FileUtils::DeleteFile(_testFile);
    }

    Core::CurlUtils _curlUtils;
    std::string _testFile, _endpoint;
    std::map <std::string, std::string> _extraHeaders;
    Core::Configuration _configuration = Core::Configuration(TMP_PROPERTIES_FILE);
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::S3Database _database = Database::S3Database(_configuration);
    S3Server _s3Server = S3Server(_configuration, _metricService);
  };

  TEST_F(S3ServerTest, BucketCreateTest) {

    // arrange

    // act
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_TRUE(response.output == CREATE_BUCKET_RESPONSE);
    EXPECT_EQ(1, bucketList.size());
  }

  TEST_F(S3ServerTest, BucketCreateVersionedTest) {

    // arrange
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();
    EXPECT_EQ(1, bucketList.size());

    // act
    Core::CurlResponse versioningResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "?versioning", _extraHeaders, VERSIONING_BODY);

    // assert
    EXPECT_TRUE(versioningResponse.statusCode == Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    EXPECT_EQ(1, bucketList.size());
  }

  TEST_F(S3ServerTest, BucketDeleteTest) {

    // arrange
    Core::CurlResponse bucketCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);

    // act
    Core::CurlResponse response = _curlUtils.SendHttpRequest("DELETE", _endpoint + "/" + BUCKET, _extraHeaders);
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    EXPECT_EQ(0, bucketList.size());
  }

  TEST_F(S3ServerTest, ObjectCreateTest) {

    // arrange
    Core::CurlResponse bucketCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    EXPECT_TRUE(bucketCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    Core::CurlResponse objectCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders, TEST_CONTENT);
    Database::Entity::S3::ObjectList objectList = _database.ListBucket(BUCKET);

    // assert
    EXPECT_TRUE(objectCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_EQ(1, objectList.size());
  }

  TEST_F(S3ServerTest, ObjectGetTest) {

    // arrange
    Core::CurlResponse bucketCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    EXPECT_TRUE(bucketCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Core::CurlResponse objectCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders, TEST_CONTENT);
    EXPECT_TRUE(objectCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    Core::CurlResponse objectGetResponse = _curlUtils.SendHttpRequest("GET", _endpoint + "/" + BUCKET + "/" + KEY,_extraHeaders);

    // assert
    EXPECT_TRUE(objectGetResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_FALSE(objectGetResponse.output.empty());
  }

  TEST_F(S3ServerTest, ObjectDeleteTest) {

    // arrange
    Core::CurlResponse bucketCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    EXPECT_TRUE(bucketCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    Core::CurlResponse objectCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders, TEST_CONTENT);
    EXPECT_TRUE(objectCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    Core::CurlResponse objectDeleteResponse = _curlUtils.SendHttpRequest("DELETE", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders);
    Database::Entity::S3::ObjectList objectList = _database.ListBucket(BUCKET);

    // assert
    EXPECT_TRUE(objectDeleteResponse.statusCode == Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    EXPECT_EQ(0, objectList.size());
  }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_S3SERVERTEST_H