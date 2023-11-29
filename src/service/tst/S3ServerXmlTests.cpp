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

  class S3ServerXmlTest : public ::testing::Test {

  protected:

    void SetUp() override {

      // Set HTTP headers
      _extraHeaders["Authorization"] = Core::AwsUtils::GetAuthorizationHeader(_configuration, "s3");
      _extraHeaders["Content-Type"] = Core::AwsUtils::GetContentTypeHeader("xml");

      // Define endpoint
      std::string _port = _configuration.getString("awsmock.service.s3.port", std::to_string(S3_DEFAULT_PORT));
      std::string _host = _configuration.getString("awsmock.service.s3.host", S3_DEFAULT_HOST);
      _endpoint = "http://" + _host + ":" + _port;

      // Start HTTP manager
      Poco::ThreadPool::defaultPool().start(_s3Server);
      while (!_s3Server.IsRunning()) {
        Poco::Thread::sleep(500);
      }
    }

    void TearDown() override {
      _s3Server.StopServer();
      _database.DeleteAllBuckets();
    }

    Core::CurlUtils _curlUtils;
    std::string _endpoint;
    std::map<std::string, std::string> _extraHeaders;
    Core::Configuration _configuration = Core::TestUtils::GetTestConfiguration();
    Core::MetricService _metricService = Core::MetricService(_configuration);
    Database::S3Database _database = Database::S3Database(_configuration);
    S3Server _s3Server = S3Server(_configuration, _metricService);
  };

  TEST_F(S3ServerXmlTest, BucketCreateTest) {

    // arrange

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "mb");
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_TRUE(Core::StringUtils::Contains(response.output, "BucketArn"));
    EXPECT_EQ(1, bucketList.size());
  }

  TEST_F(S3ServerXmlTest, BucketCreateVersionedTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "mb");
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();
    EXPECT_EQ(1, bucketList.size());

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "cp");
    Core::CurlResponse versioningResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "?versioning", _extraHeaders, VERSIONING_BODY);

    // assert
    EXPECT_TRUE(versioningResponse.statusCode == Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    EXPECT_EQ(1, bucketList.size());
  }

  TEST_F(S3ServerXmlTest, BucketDeleteTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "mb");
    Core::CurlResponse bucketCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "rb");
    Core::CurlResponse response = _curlUtils.SendHttpRequest("DELETE", _endpoint + "/" + BUCKET, _extraHeaders);
    Database::Entity::S3::BucketList bucketList = _database.ListBuckets();

    // assert
    EXPECT_TRUE(response.statusCode == Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    EXPECT_EQ(0, bucketList.size());
  }

  TEST_F(S3ServerXmlTest, ObjectCreateTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "mb");
    Core::CurlResponse bucketCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    EXPECT_TRUE(bucketCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "cp");
    Core::CurlResponse objectCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders, TEST_CONTENT);
    Database::Entity::S3::ObjectList objectList = _database.ListBucket(BUCKET);

    // assert
    EXPECT_TRUE(objectCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_EQ(1, objectList.size());
  }

  TEST_F(S3ServerXmlTest, ObjectGetTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "mb");
    Core::CurlResponse bucketCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    EXPECT_TRUE(bucketCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "cp");
    Core::CurlResponse objectCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders, TEST_CONTENT);
    EXPECT_TRUE(objectCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "cp");
    Core::CurlResponse objectGetResponse = _curlUtils.SendHttpRequest("GET", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders);

    // assert
    EXPECT_TRUE(objectGetResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    EXPECT_FALSE(objectGetResponse.output.empty());
  }

  TEST_F(S3ServerXmlTest, ObjectDeleteTest) {

    // arrange
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "mb");
    Core::CurlResponse bucketCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET, _extraHeaders, LOCATION_CONSTRAINT);
    EXPECT_TRUE(bucketCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "cp");
    Core::CurlResponse objectCreateResponse = _curlUtils.SendHttpRequest("PUT", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders, TEST_CONTENT);
    EXPECT_TRUE(objectCreateResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK);

    // act
    _extraHeaders["User-Agent"] = Core::AwsUtils::GetUserAgentHeader("s3", "rm");
    Core::CurlResponse objectDeleteResponse = _curlUtils.SendHttpRequest("DELETE", _endpoint + "/" + BUCKET + "/" + KEY, _extraHeaders);
    Database::Entity::S3::ObjectList objectList = _database.ListBucket(BUCKET);

    // assert
    EXPECT_TRUE(objectDeleteResponse.statusCode == Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    EXPECT_EQ(0, objectList.size());
  }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_S3SERVERTEST_H