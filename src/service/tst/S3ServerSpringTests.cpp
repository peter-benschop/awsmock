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
#define TEST_PORT 10100

namespace AwsMock::Service {

    namespace http = boost::beast::http;

    /**
     * Tests the aws-sdk-java interface to the AwsMock system.
     *
     * <p>The aws-mock-java-test.jar file should be installed in <pre>/usr/local/lib</pre>.</p>
     */
    class S3ServerSpringTest : public ::testing::Test {

      protected:

        void SetUp() override {

            // General configuration
            _region = _configuration.getString("awsmock.region", "eu-central-1");

            // Define endpoint. This is the endpoint of the SQS server, not the gateway
            _configuration.setInt("awsmock.service.gateway.http.port", TEST_PORT + 1);
            _configuration.setString("awsmock.service.gateway.http.host", "localhost");

            // Base URL
            _baseUrl = "/api/s3/";

            // Start HTTP manager
            _gatewayServer = std::make_shared<Service::GatewayServer>(ioc);
            _gatewayServer->Initialize();
            _gatewayServer->Start();
        }

        void TearDown() override {
            _s3Database.DeleteAllObjects();
            _s3Database.DeleteAllBuckets();
            _gatewayServer->Stop();
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

        std::string _region, _baseUrl;
        boost::asio::io_context ioc{2};
        Core::Configuration &_configuration = Core::Configuration::instance();
        Core::MetricService &_metricService = Core::MetricService::instance();
        Database::S3Database &_s3Database = Database::S3Database::instance();
        std::shared_ptr<Service::GatewayServer> _gatewayServer;
    };

    TEST_F(S3ServerSpringTest, S3CreateBucketTest) {

        // arrange

        // act
        Core::HttpSocketResponse result = SendPostCommand(_baseUrl + "createBucket?bucketName=" + Core::StringUtils::UrlEncode(TEST_BUCKET), {});
        long buckets = _s3Database.BucketCount();

        // assert
        EXPECT_TRUE(result.statusCode == http::status::ok);
        EXPECT_EQ(1, buckets);
    }

    TEST_F(S3ServerSpringTest, S3DeleteBucketTest) {

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

    TEST_F(S3ServerSpringTest, S3PutObjectTest) {

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

    TEST_F(S3ServerSpringTest, S3GetObjectTest) {

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

    TEST_F(S3ServerSpringTest, S3UploadObjectTest) {

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

    TEST_F(S3ServerSpringTest, S3DownloadObjectTest) {

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

}// namespace AwsMock::Service

#endif// AWMOCK_S3_SPRING_SERVER_TEST_H