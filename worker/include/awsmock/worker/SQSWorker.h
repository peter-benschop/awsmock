//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_WORKER_SQSWORKER_H
#define AWSMOCK_WORKER_SQSWORKER_H

// C++ standard includes
#include <string>
#include <sys/inotify.h>

// Poco includes
#include "Poco/Delegate.h"
#include <Poco/DirectoryWatcher.h>
#include <Poco/Logger.h>
#include <Poco/Path.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/Logger.h>
#include <awsmock/db/SQSDatabase.h>

namespace AwsMock::Worker {

    class SQSWorker : public Poco::Runnable {

    public:

      /**
       * Constructor
       */
      explicit SQSWorker(const Core::Configuration &configuration);

      /**
       * Destructor
       */
      ~SQSWorker() override;

      /**
       * Main method
       */
      [[noreturn]] void run() override;

    private:

      /**
       * Initialization
       */
      void Initialize();

      /**
       * Set messages
       */
      void ResetMessages();

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * S3 service
       */
      std::unique_ptr<Database::SQSDatabase> _sqsDatabase;

      /**
       * AWS region
       */
      std::string _region;
    };

} // namespace AwsMock::Worker

#endif //AWSMOCK_WORKER_S3WORKER_H
