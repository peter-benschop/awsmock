//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_SERVICE_SNSSERVER_H
#define AWSMOCK_SERVICE_SNSSERVER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ThreadPool.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/AbstractServer.h>
#include <awsmock/service/SNSMonitoring.h>
#include <awsmock/service/SNSHandlerFactory.h>

#define SNS_DEFAULT_PORT 9502
#define SNS_DEFAULT_HOST "localhost"
#define SNS_DEFAULT_QUEUE_LENGTH  250
#define SNS_DEFAULT_THREADS 50
#define SNS_DEFAULT_TIMEOUT 120

namespace AwsMock::Service {

  class SNSServer : public AbstractServer {

  public:

    /**
     * Constructor
     *
     * @param configuration aws-mock configuration
     * @param metricService aws-mock monitoring module
     */
    explicit SNSServer(Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Destructor
     */
    ~SNSServer() override;

    /**
     * Main method
     */
    void MainLoop() override;

    /**
     * Stop monitoring
     */
    void StopMonitoringServer();

  private:

    /**
     * Start monitoring
     */
    void StartMonitoringServer();

    /**
     * Reset messages
     *
     * <p>Loops over all SQS queues and sets the state to INITIAL in case the visibilityTimeout timeout has been reached. Also the retry count in increased by one.</p>
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
     * Metric module
     */
    Core::MetricService &_metricService;

    /**
     * Service database
     */
    std::unique_ptr<Database::ModuleDatabase> _serviceDatabase;

    /**
     * S3 module
     */
    std::unique_ptr<Database::SQSDatabase> _sqsDatabase;

    /**
     * Thread pool
     */
    AwsMock::Core::ThreadPool<SNSMonitoring> _threadPool;

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

#endif // AWSMOCK_SERVICE_SNSSERVER_H
