//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWMOCK_CORE_DATABASETEST_H
#define AWMOCK_CORE_DATABASETEST_H

// GTest includes
#include <gtest/gtest.h>

// Poco includes
#include "Poco/Path.h"

// Local includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/db/S3Database.h>

#define REGION "eu-central-1"
#define BUCKET "test-bucket"
#define OWNER "test-owner"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    class S3DatabaseTest : public ::testing::Test {

    protected:

      void SetUp() override {
      }

      void TearDown() override {
          Poco::Data::Statement stmt(_session);
          stmt << "DELETE FROM s3_notification;"
                  "DELETE FROM s3_object;"
                  "DELETE FROM s3_bucket;", now;
      }

      Core::Configuration _configuration = Core::Configuration("/tmp/aws-mock.properties");
      S3Database _database = S3Database(_configuration);
      Poco::Data::Session _session = _database.GetSession();
    };

    TEST_F(S3DatabaseTest, ConstructorTest) {

        // arrange
        int count = 0;

        // act
        Poco::Data::Statement stmt(_session);
        stmt << "SELECT COUNT(*) FROM s3_bucket", into(count), now;

        // assert
        EXPECT_EQ(count, 0);
    }

    TEST_F(S3DatabaseTest, BucketCreateTest) {

        // arrange
        Entity::S3::Bucket bucket = {.name=BUCKET, .region=REGION, .owner=OWNER};

        // act
        Entity::S3::Bucket result = _database.CreateBucket(bucket);

        // assert
        EXPECT_TRUE(result.name == BUCKET);
        EXPECT_TRUE(result.region == REGION);
    }

    TEST_F(S3DatabaseTest, BucketExistsTest) {

        // arrange
        Entity::S3::Bucket bucket = {.name=BUCKET, .region=REGION, .owner=OWNER};
        _database.CreateBucket(bucket);

        // act
        bool result = _database.BucketExists(bucket.region, bucket.name);

        // assert
        EXPECT_TRUE(result);
    }

    TEST_F(S3DatabaseTest, BucketGetByIdTest) {

        // arrange
        Entity::S3::Bucket bucket = {.name=BUCKET, .region=REGION, .owner=OWNER};
        _database.CreateBucket(bucket);

        // act
        bool result = _database.BucketExists(bucket.region, bucket.name);

        // assert
        EXPECT_TRUE(result);
    }

    TEST_F(S3DatabaseTest, BucketListTest) {

        // arrange
        Entity::S3::Bucket bucket = {.name=BUCKET, .region=REGION, .owner=OWNER};
        _database.CreateBucket(bucket);

        // act
        Entity::S3::BucketList result = _database.ListBuckets();

        // assert
        EXPECT_EQ(result.size() ,1);
    }

    TEST_F(S3DatabaseTest, BucketListObjectTest) {

        // arrange
        Entity::S3::Bucket bucket = {.name=BUCKET, .region=REGION, .owner=OWNER};
        _database.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket=bucket.name, .owner=OWNER, .size=5};
        _database.CreateObject(object);

        // act
        Entity::S3::ObjectList result = _database.ListBucket(bucket.name);

        // assert
        EXPECT_EQ(result.size() ,1);
    }

    TEST_F(S3DatabaseTest, BucketDeleteTest) {

        // arrange
        Entity::S3::Bucket bucket = {.name=BUCKET, .region=REGION, .owner=OWNER};
        bucket = _database.CreateBucket(bucket);

        // act
        EXPECT_NO_THROW({ _database.DeleteBucket(bucket); });
        bool result = _database.BucketExists(bucket.region, bucket.name);

        // assert
        EXPECT_FALSE(result);
    }

    TEST_F(S3DatabaseTest, ObjectCreateTest) {

        // arrange
        Entity::S3::Bucket bucket = {.name=BUCKET, .region=REGION, .owner=OWNER};
        bucket = _database.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket=bucket.name, .owner=OWNER, .size=5};
        object = _database.CreateObject(object);

        // act
        Entity::S3::Object result = _database.GetObject(object.bucket, object.key);

        // assert
        EXPECT_STREQ(result.key.c_str(), object.key.c_str());
    }

    TEST_F(S3DatabaseTest, ObjectByIdTest) {

        // arrange
        Entity::S3::Bucket bucket = {.name=BUCKET, .region=REGION, .owner=OWNER};
        bucket = _database.CreateBucket(bucket);
        Entity::S3::Object object = {.bucket=bucket.name, .owner=OWNER, .size=5};
        object = _database.CreateObject(object);

        // act
        Entity::S3::Object result = _database.GetObjectById(object.id);

        // assert
        EXPECT_EQ(result.id, object.id);
    }

    TEST_F(S3DatabaseTest, CreateNotificationTest) {

        // arrange
        Entity::S3::BucketNotification notification = {.bucket=BUCKET, .region=REGION, .function="aws:arn:000000000:lambda:test", .event="Created:*"};

        // act
        Entity::S3::BucketNotification result = _database.CreateBucketNotification(notification);

        // assert
        EXPECT_TRUE(result.id > 0);
    }

} // namespace AwsMock::Core

#endif // AWMOCK_CORE_DIRUTILSTEST_H