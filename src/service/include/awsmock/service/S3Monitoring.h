//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_SERVICE_S3MONITORING_H
#define AWSMOCK_SERVICE_S3MONITORING_H

// C++ standard includes
#include <string>
#include <iostream>
#include <sys/inotify.h>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/Logger.h>
#include <Poco/Path.h>
#include <Poco/Runnable.h>
#include <Poco/ScopedLock.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/DirectoryWatcher.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/LogStream.h>
#include "awsmock/core/MetricService.h"
#include "awsmock/core/ResourceNotFoundException.h"
#include <awsmock/dto/s3/CreateBucketConstraint.h>
#include <awsmock/dto/s3/PutObjectRequest.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/AbstractWorker.h>

#define S3_MONITORING_DEFAULT_PERIOD 60000

namespace AwsMock::Service {

  class S3Monitoring : public Poco::Runnable {

    public:

      /**
       * Constructor
       *
       * @param configuration aws-mock configuration
       * @param metricService aws-mock monitoring
       * @param condition stop condition
       */
      explicit S3Monitoring(const Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition);

      ~S3Monitoring() override;

      /**
       * Main method
       */
      void run() override;

      /**
       * Return running flag
       *
       * @return true if thread is running
       */
      bool GetRunning() const { return _running; }

      void Stop();

    private:

      /**
       * Update metric counters
       */
      void UpdateCounters();

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Metric service
       */
      Core::MetricService &_metricService;

      /**
       * S3 database
       */
      std::unique_ptr<Database::S3Database> _s3Database;

      /**
       * S3 monitoring period in seconds
       */
      int _period;

      /**
       * Running flag
       */
      bool _running;

      /**
       * Shutdown condition
       */
      Poco::Condition &_condition;

      /**
       * Shutdown mutex
       */
      Poco::Mutex _mutex;
  };

} // namespace AwsMock::Worker

#endif // AWSMOCK_SERVICE_S3MONITORING_H
