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
#include <awsmock/dto/s3/ListAllBucketResponse.h>
#include <awsmock/db/Database.h>

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
       * @param region AWS region
       * @param name bucket name
       * @param owner bucket owner
       * @throws DatabaseException
       */
      void CreateBucket(const std::string &region, const std::string &name, const std::string &owner);

      /**
       * Create a new S3 object in the S3 object table
       *
       * @param bucket bucket name
       * @param key object name
       * @param owner bucket owner
       * @throws DatabaseException
       */
      void CreateObject(const std::string &bucket, const std::string &key, const std::string &owner);

      /**
       * List all buckets
       *
       * @return ListAllBucketResponse
       */
      Dto::S3::BucketList ListBuckets();

      /**
       * Delete a bucket.
       *
       * @param region AWS region
       * @param name bucket name
       * @throws DatabaseException
       */
      void DeleteBucket(const std::string &region, const std::string &name);

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

    };

} // namespace AwsMock::Database

#endif //AWSMOCK_DB_S3DATABASE_H
