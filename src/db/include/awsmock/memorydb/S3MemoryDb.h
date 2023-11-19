//
// Created by vogje01 on 11/19/23.
//

#ifndef AWSMOCK_REPOSITORY_S3MEMORYDB_H
#define AWSMOCK_REPOSITORY_S3MEMORYDB_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/SingletonHolder.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/s3/Bucket.h>
#include <awsmock/entity/s3/Object.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

  class S3MemoryDb {

  public:

    /**
     * Constructor
     */
    S3MemoryDb();

    /**
     * Singleton instance
     */
    static S3MemoryDb &instance() {
      static Poco::SingletonHolder<S3MemoryDb> sh;
      return *sh.get();
    }

    /**
     * List all buckets
     *
     * @return BucketList
     */
    Entity::S3::BucketList ListBuckets();

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
     * List all objects.
     *
     * @param prefix S3 key prefix
     * @return ObjectList
     */
    Entity::S3::ObjectList ListObjects(const std::string &prefix = {});

    /**
     * Counts the number of keys in a bucket
     *
     * @param region AWS region
     * @param bucket bucket name
     * @return number of object in bucket
     * @throws DatabaseException
     */
    long ObjectCount(const std::string &region = {}, const std::string &bucket = {});

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * S3 bucket map, when running without database
     */
    std::map<std::string, Entity::S3::Bucket> _buckets;

    /**
     * S3 object map, when running without database
     */
    std::map<std::string, Entity::S3::Object> _objects;

  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_S3MEMORYDB_H
