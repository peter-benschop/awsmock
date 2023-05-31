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
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/db/Database.h>
#include <awsmock/entity/s3/Bucket.h>
#include <awsmock/entity/s3/Object.h>

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
      bool BucketExists(const std::string &region, const std::string &name);

      /**
       * Create a new bucket in the S3 bucket table
       *
       * @param bucket bucket entity
       * @throws DatabaseException
       */
      void CreateBucket(const Entity::S3::Bucket& bucket);

      /**
       * Create a new S3 object in the S3 object table
       *
       * @param object object entity
       * @throws DatabaseException
       */
      void CreateObject(const Entity::S3::Object& object);

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
       * Delete a bucket.
       *
       * @param bucket bucket entity
       * @throws DatabaseException
       */
      void DeleteBucket(const Entity::S3::Bucket& bucket);

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

    };

} // namespace AwsMock::Database

#endif //AWSMOCK_DB_S3DATABASE_H
