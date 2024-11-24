//
// Created by vogje01 on 21/10/2023.
//

#ifndef AWMOCK_S3_SPRING_SERVER_TEST_H
#define AWMOCK_S3_SPRING_SERVER_TEST_H

// GTest includes
#include <gtest/gtest.h>

// AwsMock includes
#include <awsmock/core/HttpSocket.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/gateway/GatewayServer.h>

// Test includes
#include <awsmock/core/TestUtils.h>

#define REGION std::string("eu-central-1")
#define TEST_BUCKET std::string("test-bucket")
#define TEST_KEY std::string("test-key")
#define TEST_BUCKET_COPY std::string("test-bucket-copy")
#define TEST_KEY_COPY std::string("test-key-copy")
#define TEST_PORT 10100

namespace AwsMock::Service {

    namespace http = boost::beast::http;

    /**
     * Tests the aws-sdk-java interface to the AwsMock system.
     *
     * <p>The aws-mock-java-test.jar file should be installed in <pre>/usr/local/lib</pre>.</p>
     */
    class S3ServerJavaTest : public ::testing::Test {

      protected:

        void SetUp() override {

            // General configuration
            _region = _configuration.GetValueString("awsmock.region");

            // Define endpoint. This is the endpoint of the SQS server, not the gateway
            _configuration.SetValue("awsmock.service.gateway.http.port", TEST_PORT + 1);
            _configuration.SetValue("awsmock.service.gateway.http.host", "localhost");

            // Base URL
            _baseUrl = "/api/s3/";

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(_ios);
            _thread = boost::thread([&]() {
                boost::asio::io_service::work work(_ios);
                _ios.run();
            });
        }

        void TearDown() override {
            _s3Database.DeleteAllObjects();
            _s3Database.DeleteAllBuckets();
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

        static Core::HttpSocketResponse SendPutCommand(const std::string &url, const std::string &payload) {
            std::map<std::string, std::string> headers;
            headers[to_string(http::field::content_type)] = "application/json";
            Core::HttpSocketResponse response = Core::HttpSocket::SendJson(http::verb::put, "localhost", TEST_PORT, url, payload, headers);
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

        boost::thread _thread;
        std::string _region, _baseUrl;
        boost::asio::io_service _ios{10};
        Core::YamlConfiguration &_configuration = Core::YamlConfiguration::instance();
        Monitoring::MetricService &_metricService = Monitoring::MetricService::instance();
        Database::S3Database &_s3Database = Database::S3Database::instance();
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
    };

    TEST_F(S3ServerJavaTest, S3CreateBucketTest) {

        // arrange

        // act
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        long buckets = _s3Database.BucketCount();

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_EQ(1, buckets);
    }

    TEST_F(S3ServerJavaTest, S3ListBucketTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);

        // act
        Core::HttpSocketResponse listResult = SendGetCommand(_baseUrl + "listBuckets", {});

        // assert
        EXPECT_TRUE(listResult.statusCode == http::status::ok);
        EXPECT_EQ(1, buckets);
    }

    TEST_F(S3ServerJavaTest, S3PutBucketVersioningTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);

        // act
        Core::HttpSocketResponse versioningResult = SendPutCommand(_baseUrl + "putBucketVersioning?bucket=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        Database::Entity::S3::Bucket bucket = _s3Database.GetBucketByRegionName(REGION, TEST_BUCKET);

        // assert
        EXPECT_TRUE(versioningResult.statusCode == http::status::ok);
        EXPECT_TRUE(bucket.versionStatus == Database::Entity::S3::BucketVersionStatus::ENABLED);
    }

    TEST_F(S3ServerJavaTest, S3ListObjectVersionsTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);
        Core::HttpSocketResponse versioningResult = SendPutCommand(_baseUrl + "putBucketVersioning?bucket=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        Database::Entity::S3::Bucket bucket = _s3Database.GetBucketByRegionName(REGION, TEST_BUCKET);
        EXPECT_TRUE(versioningResult.statusCode == http::status::ok);
        EXPECT_TRUE(bucket.versionStatus == Database::Entity::S3::BucketVersionStatus::ENABLED);
        Core::HttpSocketResponse putObjectResult1 = SendPutCommand(_baseUrl + "putObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=1", {});
        EXPECT_TRUE(putObjectResult1.statusCode == http::status::ok);
        EXPECT_EQ(1, _s3Database.ObjectCount(REGION, TEST_BUCKET));
        Core::HttpSocketResponse putObjectResult2 = SendPutCommand(_baseUrl + "putObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=1", {});
        EXPECT_TRUE(putObjectResult2.statusCode == http::status::ok);
        EXPECT_EQ(2, _s3Database.ObjectCount(REGION, TEST_BUCKET));

        // act
        Core::HttpSocketResponse listVersionsResult = SendGetCommand(_baseUrl + "listObjectVersions?bucket=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&prefix=test", {});
        int versions = std::stoi(listVersionsResult.body);

        // assert
        EXPECT_TRUE(versioningResult.statusCode == http::status::ok);
        EXPECT_EQ(2, versions);
    }

    TEST_F(S3ServerJavaTest, S3DeleteBucketTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);

        // act
        Core::HttpSocketResponse deleteResult = SendDeleteCommand(_baseUrl + "deleteBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        buckets = _s3Database.BucketCount();

        // assert
        EXPECT_TRUE(deleteResult.statusCode == http::status::ok);
        EXPECT_EQ(0, buckets);
    }

    TEST_F(S3ServerJavaTest, S3PutObjectTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);

        // act
        Core::HttpSocketResponse putObjectResult = SendPutCommand(_baseUrl + "putObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=1", {});
        long objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);

        // assert
        EXPECT_TRUE(putObjectResult.statusCode == http::status::ok);
        EXPECT_EQ(1, objects);
    }

    TEST_F(S3ServerJavaTest, S3GetObjectTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);
        Core::HttpSocketResponse putObjectResult = SendPutCommand(_baseUrl + "putObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=1", {});
        long objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        EXPECT_EQ(1, objects);

        // act
        Core::HttpSocketResponse getObjectResult = SendGetCommand(_baseUrl + "getObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY), {});
        objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);

        // assert
        EXPECT_TRUE(getObjectResult.statusCode == http::status::ok);
        EXPECT_EQ(1, objects);
    }

    TEST_F(S3ServerJavaTest, S3GetSizeTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);
        Core::HttpSocketResponse putObjectResult = SendPutCommand(_baseUrl + "putObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=1", {});
        long objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        EXPECT_EQ(1, objects);

        // act
        Core::HttpSocketResponse getObjectResult = SendGetCommand(_baseUrl + "getHead?bucket=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY), {});
        long size = std::stol(getObjectResult.body);

        // assert
        EXPECT_TRUE(getObjectResult.statusCode == http::status::ok);
        EXPECT_TRUE(size > 0);
    }

    TEST_F(S3ServerJavaTest, S3UploadObjectTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);

        // act
        Core::HttpSocketResponse uploadObjectResult = SendGetCommand(_baseUrl + "uploadObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=10", {});
        long objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        EXPECT_EQ(1, objects);

        // assert
        EXPECT_TRUE(uploadObjectResult.statusCode == http::status::ok);
        EXPECT_EQ(1, objects);
    }

    TEST_F(S3ServerJavaTest, S3DownloadObjectTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);
        Core::HttpSocketResponse uploadObjectResult = SendGetCommand(_baseUrl + "uploadObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=10", {});
        EXPECT_TRUE(uploadObjectResult.statusCode == http::status::ok);
        long objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        EXPECT_EQ(1, objects);

        // act
        Core::HttpSocketResponse downloadObjectResult = SendGetCommand(_baseUrl + "downloadObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY), {});

        // assert
        EXPECT_TRUE(downloadObjectResult.statusCode == http::status::ok);
        EXPECT_EQ(1, objects);
    }

    TEST_F(S3ServerJavaTest, S3CopyObjectTest) {

        // arrange
        Core::HttpSocketResponse createResult1 = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult1.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);
        Core::HttpSocketResponse createResult2 = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET_COPY), {});
        EXPECT_TRUE(createResult2.statusCode == http::status::ok);
        buckets = _s3Database.BucketCount();
        EXPECT_EQ(2, buckets);
        Core::HttpSocketResponse uploadObjectResult = SendGetCommand(_baseUrl + "uploadObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=1", {});
        EXPECT_TRUE(uploadObjectResult.statusCode == http::status::ok);
        long objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        EXPECT_EQ(1, objects);

        // act
        Core::HttpSocketResponse copyObjectResult = SendPostCommand(_baseUrl + "copyObject?sourceBucket=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&sourceKey=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&destinationBucket=" + Core::StringUtils::UrlEncode(TEST_BUCKET_COPY) + "&destinationKey=" + Core::StringUtils::UrlEncode(TEST_KEY_COPY), {});
        EXPECT_TRUE(copyObjectResult.statusCode == http::status::ok);
        long objects1 = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        long objects2 = _s3Database.ObjectCount(REGION, TEST_BUCKET_COPY);

        // assert
        EXPECT_TRUE(copyObjectResult.statusCode == http::status::ok);
        EXPECT_EQ(1, objects1);
        EXPECT_EQ(1, objects2);
    }

    TEST_F(S3ServerJavaTest, S3CopyBigObjectTest) {

        // arrange
        Core::HttpSocketResponse createResult1 = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult1.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);
        Core::HttpSocketResponse createResult2 = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET_COPY), {});
        EXPECT_TRUE(createResult2.statusCode == http::status::ok);
        buckets = _s3Database.BucketCount();
        EXPECT_EQ(2, buckets);
        Core::HttpSocketResponse uploadObjectResult = SendGetCommand(_baseUrl + "uploadObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=200", {});
        EXPECT_TRUE(uploadObjectResult.statusCode == http::status::ok);
        long objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        EXPECT_EQ(1, objects);

        // act
        Core::HttpSocketResponse copyObjectResult = SendPostCommand(_baseUrl + "copyBigObject?sourceBucket=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&sourceKey=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&destinationBucket=" + Core::StringUtils::UrlEncode(TEST_BUCKET_COPY) + "&destinationKey=" + Core::StringUtils::UrlEncode(TEST_KEY_COPY), {});
        EXPECT_TRUE(copyObjectResult.statusCode == http::status::ok);
        long objects1 = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        long objects2 = _s3Database.ObjectCount(REGION, TEST_BUCKET_COPY);

        // assert
        EXPECT_TRUE(copyObjectResult.statusCode == http::status::ok);
        EXPECT_EQ(1, objects1);
        EXPECT_EQ(1, objects2);
    }

    TEST_F(S3ServerJavaTest, S3DeleteObjectTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);
        Core::HttpSocketResponse uploadObjectResult = SendGetCommand(_baseUrl + "uploadObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=1", {});
        EXPECT_TRUE(uploadObjectResult.statusCode == http::status::ok);
        long objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        EXPECT_EQ(1, objects);

        // act
        Core::HttpSocketResponse deleteObjectResult = SendDeleteCommand(_baseUrl + "deleteObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY), {});
        EXPECT_TRUE(deleteObjectResult.statusCode == http::status::ok);
        objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);

        // assert
        EXPECT_TRUE(deleteObjectResult.statusCode == http::status::ok);
        EXPECT_EQ(0, objects);
    }

    TEST_F(S3ServerJavaTest, S3DeleteObjectsTest) {

        // arrange
        Core::HttpSocketResponse createResult = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        EXPECT_TRUE(createResult.statusCode == http::status::ok);
        long buckets = _s3Database.BucketCount();
        EXPECT_EQ(1, buckets);
        Core::HttpSocketResponse uploadObjectResult1 = SendGetCommand(_baseUrl + "uploadObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&size=1", {});
        EXPECT_TRUE(uploadObjectResult1.statusCode == http::status::ok);
        long objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        EXPECT_EQ(1, objects);
        Core::HttpSocketResponse uploadObjectResult2 = SendGetCommand(_baseUrl + "uploadObject?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key=" + Core::StringUtils::UrlEncode(TEST_KEY_COPY) + "&size=1", {});
        EXPECT_TRUE(uploadObjectResult2.statusCode == http::status::ok);
        objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);
        EXPECT_EQ(2, objects);

        // act
        Core::HttpSocketResponse deleteObjectResult = SendDeleteCommand(_baseUrl + "deleteObjects?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET) + "&key1=" + Core::StringUtils::UrlEncode(TEST_KEY) + "&key2=" + Core::StringUtils::UrlEncode(TEST_KEY_COPY), {});
        EXPECT_TRUE(deleteObjectResult.statusCode == http::status::ok);
        objects = _s3Database.ObjectCount(REGION, TEST_BUCKET);

        // assert
        EXPECT_TRUE(deleteObjectResult.statusCode == http::status::ok);
        EXPECT_EQ(0, objects);
    }

}// namespace AwsMock::Service

#endif// AWMOCK_S3_SPRING_SERVER_TEST_H