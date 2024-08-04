//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_S3MEMORYDBTEST_H
#define AWMOCK_CORE_S3MEMORYDBTEST_H

// C++ standard includes
#include <iostream>
#include <vector>

// GTest includes
#include <gtest/gtest.h>

// Local includes
#include "awsmock/core/config/Configuration.h"
#include <awsmock/core/TestUtils.h>
#include <awsmock/repository/S3Database.h>

// MongoDB includes
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/client.hpp>

#define BUCKET "test-bucket"
#define OBJECT "test-object"
#define OWNER "test-owner"

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    class S3MemoryDbTest : public ::testing::Test {

      protected:

        void SetUp() override {
            _region = _configuration.getString("awsmock.region");
        }

        void TearDown() override {
            _servicedatabase.DeleteAllBuckets();
            _servicedatabase.DeleteAllObjects();
        }

        std::string _region;
        Core::Configuration &_configuration = Core::TestUtils::GetTestConfiguration(false);
        S3Database _servicedatabase = S3Database();
    };

    TEST_F(S3MemoryDbTest, BucketCreateTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};

        // act
        Entity::S3::Bucket result = _servicedatabase.CreateBucket(bucket);

        // assert
        EXPECT_TRUE(result.name == BUCKET);
        EXPECT_TRUE(result.region == _region);
    }

    TEST_F(S3MemoryDbTest, BucketCountTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);

        // act
        long result = _servicedatabase.BucketCount();

        // assert
        EXPECT_EQ(1, result);
    }

    TEST_F(S3MemoryDbTest, BucketExistsTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);

        // act
        bool result = _servicedatabase.BucketExists(bucket);

        // assert
        EXPECT_TRUE(result);
    }

    TEST_F(S3MemoryDbTest, BucketByRegionNameTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);

        // act
        Entity::S3::Bucket result = _servicedatabase.GetBucketByRegionName(bucket.region, bucket.name);

        // assert
        EXPECT_TRUE(result.name == bucket.name);
        EXPECT_TRUE(result.region == _region);
    }

    TEST_F(S3MemoryDbTest, BucketGetByIdTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);

        // act
        Entity::S3::Bucket result = _servicedatabase.GetBucketById(bucket.oid);

        // assert
        EXPECT_EQ(result.oid, bucket.oid);
    }

    TEST_F(S3MemoryDbTest, BucketListTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        _servicedatabase.CreateBucket(bucket);

        // act
        Entity::S3::BucketList result = _servicedatabase.ListBuckets();

        // assert
        EXPECT_EQ(result.size(), 1);
    }

    TEST_F(S3MemoryDbTest, BucketListObjectTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        _servicedatabase.CreateBucket(bucket);
        Entity::S3::Object object1 = {.bucket = bucket.name, .key = OBJECT, .owner = OWNER, .size = 5};
        _servicedatabase.CreateObject(object1);
        Entity::S3::Object object2 = {.bucket = bucket.name, .key = "test1/" + std::string(OBJECT), .owner = OWNER, .size = 5};
        _servicedatabase.CreateObject(object2);

        // act
        Entity::S3::ObjectList result1 = _servicedatabase.ListBucket(bucket.name);
        Entity::S3::ObjectList result2 = _servicedatabase.ListBucket(bucket.name, "test1");

        // assert
        EXPECT_EQ(result1.size(), 2);
        EXPECT_EQ(result2.size(), 1);
    }

    TEST_F(S3MemoryDbTest, BucketHasObjetsTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        _servicedatabase.CreateBucket(bucket);
        Entity::S3::Object object1 = {.region = _region, .bucket = bucket.name, .key = OBJECT, .owner = OWNER, .size = 5};
        _servicedatabase.CreateObject(object1);
        Entity::S3::Object
                object2 = {.region = _region, .bucket = bucket.name, .key = "test1/" + std::string(OBJECT), .owner = OWNER, .size = 5};
        _servicedatabase.CreateObject(object2);

        // act
        bool result = _servicedatabase.HasObjects(bucket);

        // assert
        EXPECT_TRUE(result);
    }

    TEST_F(S3MemoryDbTest, BucketDeleteTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);

        // act
        EXPECT_NO_THROW({ _servicedatabase.DeleteBucket(bucket); });
        bool result = _servicedatabase.BucketExists({.region = bucket.region, .name = bucket.name});

        // assert
        EXPECT_FALSE(result);
    }

    TEST_F(S3MemoryDbTest, BucketDeleteAllTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);

        // act
        EXPECT_NO_THROW({ _servicedatabase.DeleteAllBuckets(); });
        bool result = _servicedatabase.BucketExists({.region = bucket.region, .name = bucket.name});

        // assert
        EXPECT_FALSE(result);
    }

    TEST_F(S3MemoryDbTest, ObjectExistsTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket = bucket.name, .key = OBJECT, .owner = OWNER, .size = 5};
        object = _servicedatabase.CreateObject(object);

        // act
        bool result = _servicedatabase.ObjectExists(object);

        // assert
        EXPECT_TRUE(result);
    }

    TEST_F(S3MemoryDbTest, ObjectCreateTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::Object object = {.region = _region, .bucket = bucket.name, .key = "TestKey", .owner = OWNER, .size = 5};
        object = _servicedatabase.CreateObject(object);

        // act
        Entity::S3::Object result = _servicedatabase.GetObject(_region, object.bucket, object.key);

        // assert
        EXPECT_TRUE(result.key == object.key);
    }

    TEST_F(S3MemoryDbTest, ObjectUpdateTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket = bucket.name, .owner = OWNER, .size = 5};
        object = _servicedatabase.CreateObject(object);
        Entity::S3::Object updateObject = {.bucket = bucket.name, .owner = OWNER, .size = object.size + 10};

        // act
        Entity::S3::Object result = _servicedatabase.UpdateObject(updateObject);

        // assert
        EXPECT_EQ(15, result.size);
    }

    TEST_F(S3MemoryDbTest, ObjectByIdTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket = bucket.name, .owner = OWNER, .size = 5};
        object = _servicedatabase.CreateObject(object);

        // act
        Entity::S3::Object result = _servicedatabase.GetObjectById(object.oid);

        // assert
        EXPECT_TRUE(result.oid == object.oid);
    }

    TEST_F(S3MemoryDbTest, ObjectDeleteTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket = bucket.name, .owner = OWNER, .size = 5};
        object = _servicedatabase.CreateObject(object);

        // act
        EXPECT_NO_THROW({ _servicedatabase.DeleteObject(object); });
        bool result = _servicedatabase.ObjectExists({.region = object.region, .bucket = object.bucket, .key = object.key});

        // assert
        EXPECT_FALSE(result);
    }

    TEST_F(S3MemoryDbTest, ObjectBucketCountTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);

        // Create objects
        for (int i = 0; i < 10; i++) {
            _servicedatabase.CreateObject({.region = _region, .bucket = bucket.name, .key = std::string(OBJECT) + std::to_string(i), .owner = OWNER});
        }

        // act
        long result = _servicedatabase.ObjectCount(bucket.region, bucket.name);

        // assert
        EXPECT_EQ(10, result);
    }

    TEST_F(S3MemoryDbTest, ObjectListTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);

        // Create objects
        for (int i = 0; i < 10; i++) {
            _servicedatabase.CreateObject({.region = _region, .bucket = bucket.name, .key = std::string(OBJECT) + std::to_string(i), .owner = OWNER});
        }

        // act
        Entity::S3::ObjectList result = _servicedatabase.ListObjects();

        // assert
        EXPECT_EQ(10, result.size());
    }

    TEST_F(S3MemoryDbTest, ObjectDeleteManyTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);

        // Create objects
        std::vector<std::string> keys;
        for (int i = 0; i < 10; i++) {
            std::string key = std::string(OBJECT) + "-" + std::to_string(i);
            keys.push_back(key);
            Entity::S3::Object object = {.bucket = bucket.name, .key = key, .owner = OWNER};
            _servicedatabase.CreateObject(object);
        }

        // act
        EXPECT_NO_THROW({ _servicedatabase.DeleteObjects(bucket.name, keys); });
        bool result = _servicedatabase.ObjectCount(bucket.region, bucket.name);

        // assert
        EXPECT_EQ(0, result);
    }

    TEST_F(S3MemoryDbTest, ObjectDeleteAllTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket = bucket.name, .owner = OWNER, .size = 5};
        object = _servicedatabase.CreateObject(object);

        // act
        EXPECT_NO_THROW({ _servicedatabase.DeleteAllObjects(); });
        bool result = _servicedatabase.ObjectExists({.region = object.region, .bucket = object.bucket, .key = object.key});

        // assert
        EXPECT_FALSE(result);
    }

    TEST_F(S3MemoryDbTest, CreateNotificationTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::BucketNotification
                notification = {.event = "s3:ObjectCreated:*", .lambdaArn = "aws:arn:000000000:lambda:test"};

        // act
        Entity::S3::Bucket result = _servicedatabase.CreateBucketNotification(bucket, notification);

        // assert
        EXPECT_EQ(4, result.notifications.size());
    }

    TEST_F(S3MemoryDbTest, CreateNotificationPutTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::BucketNotification
                notification = {.event = "s3:ObjectCreated:Put", .lambdaArn = "aws:arn:000000000:lambda:test"};

        // act
        Entity::S3::Bucket result = _servicedatabase.CreateBucketNotification(bucket, notification);

        // assert
        EXPECT_EQ(1, result.notifications.size());
    }

    TEST_F(S3MemoryDbTest, CreateNotificationTwiceTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::BucketNotification
                notification = {.event = "s3:ObjectCreated:Put", .lambdaArn = "aws:arn:000000000:lambda:test"};
        bucket = _servicedatabase.CreateBucketNotification(bucket, notification);

        // act
        Entity::S3::Bucket result = _servicedatabase.CreateBucketNotification(bucket, notification);

        // assert
        EXPECT_EQ(1, result.notifications.size());
    }

    TEST_F(S3MemoryDbTest, DeleteNotificationTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::BucketNotification
                notification = {.event = "s3:ObjectCreated:*", .lambdaArn = "aws:arn:000000000:lambda:test"};
        bucket = _servicedatabase.CreateBucketNotification(bucket, notification);

        // act
        Entity::S3::Bucket result = _servicedatabase.DeleteBucketNotifications(bucket, notification);

        // assert
        EXPECT_TRUE(result.notifications.empty());
    }

    TEST_F(S3MemoryDbTest, DeleteNotificationPutTest) {

        // arrange
        Entity::S3::Bucket bucket = {.region = _region, .name = BUCKET, .owner = OWNER};
        bucket = _servicedatabase.CreateBucket(bucket);
        Entity::S3::BucketNotification
                notification = {.event = "s3:ObjectCreated:*", .lambdaArn = "aws:arn:000000000:lambda:test"};
        bucket = _servicedatabase.CreateBucketNotification(bucket, notification);
        Entity::S3::BucketNotification
                deleteNotification = {.event = "s3:ObjectCreated:Put", .lambdaArn = "aws:arn:000000000:lambda:test"};

        // act
        Entity::S3::Bucket result = _servicedatabase.DeleteBucketNotifications(bucket, deleteNotification);

        // assert
        EXPECT_EQ(3, result.notifications.size());
    }

}// namespace AwsMock::Database

#endif// AWMOCK_CORE_S3MEMORYDBTEST_H