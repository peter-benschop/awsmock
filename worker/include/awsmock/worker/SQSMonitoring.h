//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_WORKER_SQSMONITORING_H
#define AWSMOCK_WORKER_SQSMONITORING_H

// C++ standard includes
#include <string>
#include <iostream>
#include <sys/inotify.h>

// Poco includes
#include "Poco/Delegate.h"
#include <Poco/DirectoryWatcher.h>
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
#include <awsmock/repository/ServiceDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/worker/AbstractWorker.h>

#define SQS_MONITORING_DEFAULT_PERIOD 60000

namespace AwsMock::Worker {

  class SQSMonitoring : public Poco::Runnable {

    public:

    /**
     * Constructor
     *
     * @param configuration aws-mock configuration
     * @param metricService aws-mock monitoring
     */
    explicit SQSMonitoring(const Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Main method
     */
    void run() override;

    /**
     * Return running flag
     *
     * @return true if thread is running
     */
    bool GetRunning() { return _running; }

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
    std::unique_ptr<Database::SQSDatabase> _sqsDatabase;

    /**
     * S3 monitoring period in seconds
     */
    int _period;

    /**
     * Running flag
     */
    bool _running;
  };

} // namespace AwsMock::Worker

#endif // AWSMOCK_WORKER_SQSMONITORING_H
