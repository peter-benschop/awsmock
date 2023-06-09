//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_DB_S3DATABASE_H
#define AWSMOCK_DB_S3DATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"

// AwsMock includes
#include <awsmock/core/Logger.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/db/Database.h>
#include <awsmock/entity/s3/Bucket.h>
#include <awsmock/entity/s3/Object.h>
#include "awsmock/entity/s3/BucketNotification.h"

#define MAX_FILES 100

namespace AwsMock::Database {

    class S3Database : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit S3Database(const Core::Configuration &configuration);

      /**
       * Bucket exists
       *
       * @param region AWS region
       * @param name bucket name
       * @return true if bucket exists
       * @throws DatabaseException
       */
      [[deprecated("Use BucketExists(const Entity::S3::Bucket &bucket)")]]
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
       * Returns the bucket by id
       *
       * @param id bucket id
       * @return bucket, if existing
       * @throws DatabaseException
       */
      Entity::S3::Bucket GetBucketById(long id);

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
      Entity::S3::Bucket CreateBucket(const Entity::S3::Bucket& bucket);

      /**
       * CHeck whether the bucket has still objects
       *
       * @param bucket bucket entity
       * @return true if bucket exists
       * @throws DatabaseException
       */
      bool HasObjects(const Entity::S3::Bucket &bucket);

      /**
       * Create a new S3 object in the S3 object table
       *
       * @param object object entity
       * @return created object entity
       * @throws DatabaseException
       */
      Entity::S3::Object CreateObject(const Entity::S3::Object& object);

      /**
       * Create a new S3 object in the S3 object table, if it does not exist, otherwise update the exiting object.
       *
       * @param object object entity
       * @return created or updated object entity
       * @throws DatabaseException
       */
      Entity::S3::Object CreateOrUpdateObject(const Entity::S3::Object& object);

      /**
       * Updates an existing object in the S3 object table
       *
       * @param object object entity
       * @return updated object entity
       * @throws DatabaseException
       */
      Entity::S3::Object UpdateObject(const Entity::S3::Object& object);

      /**
       * Check the existence of an object
       *
       * @param object object entity
       * @return true if existing otherwise false
       * @throws DatabaseException
       */
      bool ObjectExists(const Entity::S3::Object& object);

      /**
       * Gets an object from an bucket
       *
       * @param bucket object bucket
       * @param key object key
       * @return S3 object
       * @throws DatabaseException
       */
      Entity::S3::Object GetObject(const std::string &bucket, const std::string &key);

      /**
       * Gets an object from an bucket
       *
       * @param id object ID
       * @return S3 object
       * @throws DatabaseException
       */
      Entity::S3::Object GetObjectById(long id);

      /**
       * List all buckets
       *
       * @return BucketList
       */
      Entity::S3::BucketList ListBuckets();

      /**
       * List all objects of a bucket
       *
       * @return ObjectList
       */
      Entity::S3::ObjectList ListBucket(const std::string &bucket);

      /**
       * Bucket notification exists
       *
       * @param bucketNotification bucket notification entity
       * @return true if bucket notification exists
       * @throws DatabaseException
       */
      bool BucketNotificationExists(const Entity::S3::BucketNotification &bucketNotification);

      /**
       * Creates a bucket notification-
       *
       * <p>Replaces the wildcard characters '*' with the SQLite wildcard '%'.</p>
       *
       * @param bucketNotification bucket notification
       * @return created BucketNotification entity
       */
      Entity::S3::BucketNotification CreateBucketNotification(const Entity::S3::BucketNotification &bucketNotification);

      /**
       * Returns a bucket notification by ID
       *
       * @param id notification ID
       * @return BucketNotification
       */
      Entity::S3::BucketNotification GetBucketNotificationById(long id);

      /**
       * Returns a bucket notification by configuration ID
       *
       * @param region AWS region
       * @param bucket S3 bucket
       * @param notificationId configuration ID
       * @return BucketNotification
       */
      Entity::S3::BucketNotification GetBucketNotificationByNotificationId(const std::string &region, const std::string &bucket, const std::string &notificationId);

      /**
       * Returns a notification.
       *
       * <p>Event matching uses inverse wildcard matching, as the wildcard patterns are stored in the database.</p>
       *
       * @param bucketNotification bucket notification.
       * @return BucketNotification
       */
      Entity::S3::BucketNotification GetBucketNotification(const Entity::S3::BucketNotification &bucketNotification);

      /**
       * Checks for a bucket notification
       *
       * @param bucketNotification notification
       * @return true if bucket notification exists
       */
      bool HasBucketNotification(const Entity::S3::BucketNotification &bucketNotification);

      /**
       * Delete a bucket notification
       *
       * @param notification bucket notification
       */
      void DeleteBucketNotifications(const Entity::S3::BucketNotification& notification);

      /**
       * Delete a bucket.
       *
       * @param bucket bucket entity
       * @throws DatabaseException
       */
      void DeleteBucket(const Entity::S3::Bucket& bucket);

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

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

      static std::map<std::string, std::vector<std::string>> allowedEventTypes;

    };

} // namespace AwsMock::Database

#endif //AWSMOCK_DB_S3DATABASE_H
