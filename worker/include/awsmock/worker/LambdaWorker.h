//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_WORKER_LAMBDAWORKER_H
#define AWSMOCK_WORKER_LAMBDAWORKER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/LogStream.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/Logger.h>
#include <awsmock/db/LambdaDatabase.h>
#include <awsmock/db/ServiceDatabase.h>
#include <awsmock/service/S3Service.h>

namespace AwsMock::Worker {

    class LambdaWorker : public Poco::Runnable {

    public:

      /**
       * Constructor
       */
      [[maybe_unused]] explicit LambdaWorker(const Core::Configuration &configuration);

      /**
       * Main method
       */
      void run() override;

    private:

      /**
       * Initialization
       */
      void Initialize();

      /**
       * Logger
       */
      Poco::LogStream _logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Service database
       */
      std::unique_ptr<Database::ServiceDatabase> _serviceDatabase;

      /**
       * Lambda database
       */
      std::unique_ptr<Database::LambdaDatabase> _lambdaDatabase;

      /**
       * S3 service
       */
      std::unique_ptr<Service::S3Service> _s3Service;

      /**
       * Data dir
       */
      std::string _dataDir;

      /**
       * AWS region
       */
      std::string _region;

      /**
       * Running flag
       */
      bool _running;
    };

} // namespace AwsMock::Worker

#endif //AWSMOCK_WORKER_LAMBDAWORKER_H
