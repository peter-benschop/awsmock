//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_SECRETSMANAGER_SERVER_H
#define AWSMOCK_SERVICE_SECRETSMANAGER_SERVER_H

// C++ standard includes
#include <string>
#include <chrono>
#include <condition_variable>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Runnable.h>
#include <Poco/SignalHandler.h>
#include <Poco/Condition.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ThreadPool.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/sqs/SQSMonitoring.h>
#include <awsmock/service/secretsmanager/SecretsManagerHandlerFactory.h>

#define SECRETSMANAGER_DEFAULT_PORT 9507
#define SECRETSMANAGER_DEFAULT_HOST "localhost"
#define SECRETSMANAGER_DEFAULT_QUEUE_LENGTH  250
#define SECRETSMANAGER_DEFAULT_THREADS 50
#define SECRETSMANAGER_DEFAULT_TIMEOUT 120

namespace AwsMock::Service {

  class SecretsManagerServer : public AbstractServer {

  public:

    /**
     * Constructor
     *
     * @param configuration aws-mock configuration
     * @param metricService aws-mock monitoring module
     */
    explicit SecretsManagerServer(Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Destructor
     */
    ~SecretsManagerServer() override;

    /**
     * Main method
     */
    void MainLoop() override;

    /**
     * Stop the monitoring module.
     */
    void StopMonitoringServer();

  private:

    /**
     * Start the monitoring module.
     */
    void StartMonitoringServer();

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Configuration
     */
    Core::Configuration &_configuration;

    /**
     * Metric module
     */
    Core::MetricService &_metricService;

    /**
     * S3 database
     */
    Database::ModuleDatabase& _moduleDatabase;

    /**
     * Thread pool
     */
    AwsMock::Core::ThreadPool<SQSMonitoring> _threadPool;

    /**
     * AWS region
     */
    std::string _region;

    /**
     * Sleeping period in ms
     */
    int _period;

    /**
     * Rest port
     */
    int _port;

    /**
     * Rest host
     */
    std::string _host;

    /**
     * HTTP max message queue length
     */
    int _maxQueueLength;

    /**
     * HTTP max concurrent connections
     */
    int _maxThreads;

    /**
     * HTTP request timeout in seconds
     */
    int _requestTimeout;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_SECRETSMANAGER_SERVER_H
