//
// Created by vogje01 on 11/19/23.
//

#ifndef AWSMOCK_REPOSITORY_S3MEMORYDB_H
#define AWSMOCK_REPOSITORY_S3MEMORYDB_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/Mutex.h>
#include <Poco/ScopedLock.h>
#include <Poco/SingletonHolder.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/s3/Bucket.h>
#include <awsmock/entity/s3/Object.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    /**
     * S3 in-memory database.
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class S3MemoryDb {

      public:
        /**
         * Constructor
         */
        S3MemoryDb() = default;

        /**
         * Singleton instance
         *
         * @return singleton instance
         */
        static S3MemoryDb &instance() {
            static Poco::SingletonHolder<S3MemoryDb> sh;
            return *sh.get();
        }

        /**
         * Bucket exists
         *
         * @param region AWS region
         * @param name bucket name
         * @return true if bucket exists
         * @throws DatabaseException
         */
        bool BucketExists(const std::string &region, const std::string &name);

        /**
         * Bucket exists
         *
         * @param bucket bucket entity
         * @return true if bucket exists
         * @throws DatabaseException
         */
        bool BucketExists(const Entity::S3::Bucket &bucket);

        /**
         * Returns the bucket by userPoolId
         *
         * @param oid bucket oid
         * @return bucket, if existing
         * @throws DatabaseException
         */
        Entity::S3::Bucket GetBucketById(const std::string &oid);

        /**
         * Returns the bucket by region and name.
         *
         * @param region AWS region
         * @param name bucket name
         * @return bucket entity
         */
        Entity::S3::Bucket GetBucketByRegionName(const std::string &region, const std::string &name);

        /**
         * Create a new bucket in the S3 bucket table
         *
         * @param bucket bucket entity
         * @return created bucket entity
         * @throws DatabaseException
         */
        Entity::S3::Bucket CreateBucket(const Entity::S3::Bucket &bucket);

        /**
       * List all buckets
       *
       * @return BucketList
       */
        Entity::S3::BucketList ListBuckets();

        /**
         * Check whether the bucket has still objects
         *
         * @param bucket bucket entity
         * @return true if bucket exists
         * @throws DatabaseException
         */
        bool HasObjects(const Entity::S3::Bucket &bucket);

        /**
         * List all objects of a bucket
         *
         * @param bucket S3 bucket name
         * @param prefix S3 key prefix
         * @return ObjectList
         */
        Entity::S3::ObjectList ListBucket(const std::string &bucket, const std::string &prefix = {});

        /**
         * Returns the total number of buckets
         *
         * @return total number of buckets
         * @throws DatabaseException
         */
        long BucketCount();

        /**
         * Updates a bucket
         *
         * @param bucket bucket entity
         * @return created bucket entity
         * @throws DatabaseException
         */
        Entity::S3::Bucket UpdateBucket(const Entity::S3::Bucket &bucket);

        /**
         * List all objects.
         *
         * @param prefix S3 key prefix
         * @return ObjectList
         */
        Entity::S3::ObjectList ListObjects(const std::string &prefix = {});

        /**
         * Delete a bucket.
         *
         * @param bucket bucket entity
         * @throws DatabaseException
         */
        void DeleteBucket(const Entity::S3::Bucket &bucket);

        /**
         * Deletes all buckets
         */
        void DeleteAllBuckets();

        /**
         * Check the existence of an object
         *
         * @param object object entity
         * @return true if existing otherwise false
         * @throws DatabaseException
         */
        bool ObjectExists(const Entity::S3::Object &object);

        /**
         * Create a new S3 object in the S3 object table
         *
         * @param object object entity
         * @return created object entity
         * @throws DatabaseException
         */
        Entity::S3::Object CreateObject(const Entity::S3::Object &object);

        /**
         * Updates an existing object in the S3 object table
         *
         * @param object object entity
         * @return updated object entity
         * @throws DatabaseException
         */
        Entity::S3::Object UpdateObject(const Entity::S3::Object &object);

        /**
         * Gets an object from an bucket
         *
         * @param oid object ID
         * @return S3 object
         * @throws DatabaseException
         */
        Entity::S3::Object GetObjectById(const std::string &oid);

        /**
         * Gets an object from an bucket
         *
         * @param region AWS S3 region name
         * @param bucket object bucket
         * @param key object key
         * @return S3 object
         * @throws DatabaseException
         */
        Entity::S3::Object GetObject(const std::string &region, const std::string &bucket, const std::string &key);

        /**
         * Counts the number of keys in a bucket
         *
         * @param region AWS region
         * @param bucket bucket name
         * @return number of object in bucket
         * @throws DatabaseException
         */
        long ObjectCount(const std::string &region = {}, const std::string &bucket = {});

        /**
         * Delete an object.
         *
         * @param object object entity
         * @throws DatabaseException
         */
        void DeleteObject(const Entity::S3::Object &object);

        /**
         * Updates an existing object in the S3 object table
         *
         * @param bucket bucket to delete from
         * @param keys vector of object keys
         * @throws DatabaseException
         */
        void DeleteObjects(const std::string &bucket, const std::vector<std::string> &keys);

        /**
         * Deletes all objects
         */
        void DeleteAllObjects();

      private:
        /**
         * S3 bucket map, when running without database
         */
        std::map<std::string, Entity::S3::Bucket> _buckets;

        /**
         * S3 object map, when running without database
         */
        std::map<std::string, Entity::S3::Object> _objects;

        /**
         * Bucket mutex
         */
        Poco::Mutex _bucketMutex;

        /**
         * Object mutex
         */
        Poco::Mutex _objectMutex;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_S3MEMORYDB_H
