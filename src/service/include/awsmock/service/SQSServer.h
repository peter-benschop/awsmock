//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_SQSSERVER_H
#define AWSMOCK_SERVICE_SQSSERVER_H

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
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/AbstractServer.h>
#include <awsmock/service/SQSMonitoring.h>
#include <awsmock/service/SQSHandlerFactory.h>

#define SQS_DEFAULT_PORT 9501
#define SQS_DEFAULT_HOST "localhost"
#define SQS_DEFAULT_QUEUE_LENGTH  250
#define SQS_DEFAULT_THREADS 50
#define SQS_DEFAULT_TIMEOUT 120

namespace AwsMock::Service {

  class SQSServer : public AbstractServer {

  public:

    /**
     * Constructor
     *
     * @param configuration aws-mock configuration
     * @param metricService aws-mock monitoring service
     */
    explicit SQSServer(Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Destructor
     */
    ~SQSServer() override;

    /**
     * Main method
     */
    void MainLoop() override;

    /**
     * Stop the monitoring service.
     */
    void StopMonitoringServer();

  private:

    /**
     * Start the monitoring service.
     */
    void StartMonitoringServer();

    /**
     * Reset messages
     *
     * <p>Loops over all SQS queues and sets the status to INITIAL in case the visibility timeout has been reached. Also the retry count in increased by one.</p>
     * <p>Checks also the expiration date and removed the messages, which are older than the max retention period.</>
     */
    void ResetMessages();

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Configuration
     */
    Core::Configuration &_configuration;

    /**
     * Metric service
     */
    Core::MetricService &_metricService;

    /**
     * Service database
     */
    std::unique_ptr<Database::ModuleDatabase> _serviceDatabase;

    /**
     * S3 service
     */
    std::unique_ptr<Database::SQSDatabase> _sqsDatabase;

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

#endif // AWSMOCK_SERVICE_SQSSERVER_H
