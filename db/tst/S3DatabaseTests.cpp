//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_S3DATABASETEST_H
#define AWMOCK_CORE_S3DATABASETEST_H

// C++ standard includes
#include <cstdint>
#include <iostream>
#include <vector>

// GTest includes
#include <gtest/gtest.h>

// Local includes
#include <awsmock/core/Configuration.h>
#include <awsmock/db/S3Database.h>

// MongoDB includes
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#define CONFIG_FILE "/tmp/aws-mock.properties"

#define BUCKET "test-bucket"
#define OBJECT "test-object"
#define OWNER "test-owner"

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    class S3DatabaseTest : public ::testing::Test {

    protected:

      void SetUp() override {
          _region = _configuration.getString("awsmock.region");
      }

      void TearDown() override {
          _s3database.DeleteAllBuckets();
      }

      std::string _region;
      Core::Configuration _configuration = Core::Configuration(CONFIG_FILE);
      S3Database _s3database = S3Database(_configuration);
    };

    TEST_F(S3DatabaseTest, BucketCreateTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region=_region, .name=BUCKET, .owner=OWNER};

        // act
        Entity::S3::Bucket result = _s3database.CreateBucket(bucket);

        // assert
        EXPECT_TRUE(result.name == BUCKET);
        EXPECT_TRUE(result.region == _region);
    }

    TEST_F(S3DatabaseTest, BucketExistsTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region=_region, .name=BUCKET, .owner=OWNER};
        bucket = _s3database.CreateBucket(bucket);

        // act
        bool result = _s3database.BucketExists(bucket);

        // assert
        EXPECT_TRUE(result);
    }

    TEST_F(S3DatabaseTest, BucketByRegionNameTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region=_region, .name=BUCKET, .owner=OWNER};
        bucket = _s3database.CreateBucket(bucket);

        // act
        Entity::S3::Bucket result = _s3database.GetBucketByRegionName(bucket.region, bucket.name);

        // assert
        EXPECT_TRUE(result.name == bucket.name);
        EXPECT_TRUE(result.region == _region);
    }

    TEST_F(S3DatabaseTest, BucketGetByIdTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region=_region, .name=BUCKET, .owner=OWNER};
        bucket = _s3database.CreateBucket(bucket);

        // act
        Entity::S3::Bucket result = _s3database.GetBucketById(bucket.oid);

        // assert
        EXPECT_EQ(result.oid, bucket.oid);
    }

    TEST_F(S3DatabaseTest, BucketListTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region=_region, .name=BUCKET, .owner=OWNER};
        _s3database.CreateBucket(bucket);

        // act
        Entity::S3::BucketList result = _s3database.ListBuckets();

        // assert
        EXPECT_EQ(result.size() ,1);
    }

/*    TEST_F(S3DatabaseTest, BucketListObjectTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region=REGION, .name=BUCKET, .owner=OWNER};
        _s3database.CreateBucket(bucket);
        Entity::S3::Object object1 = {.bucket=bucket.name, .key=OBJECT, .owner=OWNER, .size=5};
        _s3database.CreateObject(object1);
        Entity::S3::Object object2 = {.bucket=bucket.name, .key="test/" + std::string(OBJECT), .owner=OWNER, .size=5};
        _s3database.CreateObject(object2);

        // act
        Entity::S3::ObjectList result1 = _s3database.ListBucket(bucket.name);
        Entity::S3::ObjectList result2 = _s3database.ListBucket(bucket.name, "test");

        // assert
        EXPECT_EQ(result1.size(), 2);
        EXPECT_TRUE(result1[0].key == OBJECT);
        EXPECT_EQ(result1.size(), 1);
        EXPECT_STREQ(result1[0].key.c_str(), (std::string("test/") + std::string(OBJECT)).c_str());
    }

    TEST_F(S3DatabaseTest, BucketDeleteTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region=REGION, .name=BUCKET, .owner=OWNER};
        bucket = _s3database.CreateBucket(bucket);

        // act
        EXPECT_NO_THROW({ _s3database.DeleteBucket(bucket); });
        bool result = _s3database.BucketExists({.region=bucket.region, .name=bucket.name});

        // assert
        EXPECT_FALSE(result);
    }*/

    TEST_F(S3DatabaseTest, ObjectExistsTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region=_region, .name=BUCKET, .owner=OWNER};
        bucket = _s3database.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket=bucket.name, .key=OBJECT, .owner=OWNER, .size=5};
        object = _s3database.CreateObject(object);

        // act
        bool result = _s3database.ObjectExists(object);

        // assert
        EXPECT_TRUE(result);
    }

    /*TEST_F(S3DatabaseTest, ObjectCreateTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region=REGION, .name=BUCKET, .owner=OWNER};
        bucket = _s3database.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket=bucket.name, .owner=OWNER, .size=5};
        object = _s3database.CreateObject(object);

        // act
        Entity::S3::Object result = _s3database.GetObject(object.bucket, object.key);

        // assert
        EXPECT_STREQ(result.key.c_str(), object.key.c_str());
    }

    TEST_F(S3DatabaseTest, ObjectByIdTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region=REGION, .name=BUCKET, .owner=OWNER};
        bucket = _s3database.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket=bucket.name, .owner=OWNER, .size=5};
        object = _s3database.CreateObject(object);

        // act
        Entity::S3::Object result = _s3database.GetObjectById(object.id);

        // assert
        EXPECT_EQ(result.id, object.id);
    }

    TEST_F(S3DatabaseTest, CreateNotificationTest) {

        // arrange
        Entity::S3::BucketNotification notification = {.region=REGION, .bucket=BUCKET, .lambdaArn="aws:arn:000000000:lambda:test", .event="s3:ObjectCreated:*"};

        // act
        Entity::S3::BucketNotification result = _s3database.CreateBucketNotification(notification);

        // assert
        EXPECT_TRUE(result.id > 0);
    }

    TEST_F(S3DatabaseTest, HasNotificationTest) {

        // arrange
        Entity::S3::BucketNotification notification = {.region=REGION, .bucket=BUCKET, .lambdaArn="aws:arn:000000000:lambda:test", .event="s3:ObjectCreated:*"};
        notification = _s3database.CreateBucketNotification(notification);

        // act
        bool result = _s3database.HasBucketNotification(notification);

        // assert
        EXPECT_TRUE(result);
    }

    TEST_F(S3DatabaseTest, GetNotificationTest) {

        // arrange
        Entity::S3::BucketNotification notification = {.region=REGION, .bucket=BUCKET, .lambdaArn="aws:arn:000000000:lambda:test", .event="s3:ObjectCreated:*"};
        notification = _s3database.CreateBucketNotification(notification);

        // act
        Entity::S3::BucketNotification result = _s3database.GetBucketNotification(notification);

        // assert
        EXPECT_TRUE(result.region == notification.region);
        EXPECT_TRUE(Core::StringUtils::Contains(result.event, "%"));
    }

    TEST_F(S3DatabaseTest, GetNotificationPutTest) {

        // arrange
        Entity::S3::BucketNotification notification = {.region=REGION, .bucket=BUCKET, .lambdaArn="aws:arn:000000000:lambda:test", .event="s3:ObjectCreated:*"};
        notification = _s3database.CreateBucketNotification(notification);

        // act
        Entity::S3::BucketNotification search = {.region=REGION, .bucket=BUCKET, .lambdaArn="aws:arn:000000000:lambda:test", .event="s3:ObjectCreated:Put"};
        Entity::S3::BucketNotification result = _s3database.GetBucketNotification(search);

        // assert
        EXPECT_TRUE(result.region == notification.region);
        EXPECT_TRUE(result.event == "s3:ObjectCreated:%");
    }*/

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_S3DATABASETEST_H