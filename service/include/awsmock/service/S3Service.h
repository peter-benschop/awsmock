//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_S3SERVICE_H
#define AWSMOCK_SERVICE_S3SERVICE_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Logger.h>
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Node.h"

// AwsMock includes
#include "awsmock/core/ServiceException.h"
#include "awsmock/db/S3Database.h"
#include "awsmock/dto/s3/CreateBucketRequest.h"
#include "awsmock/dto/s3/CreateBucketResponse.h"

namespace AwsMock::Service {

    class S3Service {

    public:

      /**
       * Constructor
       *
       * @param configuration service configuration
       */
      explicit S3Service(const Core::Configuration &configuration);

      /**
       * Creates a new bucket
       *
       * @param name name of the bucket
       * @param s3Request S3 create request
       * @return CreateBucketResponse
       */
      Dto::S3::CreateBucketResponse CreateBucket(std::string &name, const Dto::S3::CreateBucketRequest &s3Request);

      /**
       * Delete a bucket
       *
       * @param name name of the bucket
       */
      void DeleteBucket(const std::string &region, const std::string &name);

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
       * Data directory
       */
      std::string _dataDir;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Database connection
       */
      std::unique_ptr<Database::S3Database> _database;
    };

} //namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_S3SERVICE_H
