//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_SQS_SERVER_H
#define AWSMOCK_SERVICE_SQS_SERVER_H

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
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/sqs/SQSHandlerFactory.h>

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
     * @param metricService aws-mock monitoring module
     */
    explicit SQSServer(Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Initialization
     */
    void Initialize() override;

    /**
     * Main method
     */
    void Run() override;

    /**
     * Shutdown
     */
    void Shutdown() override;

  private:

    /**
     * Update metric counters
     */
    void UpdateCounters();

    /**
     * Reset messages
     *
     * <p>Loops over all SQS queues and sets the state to INITIAL in case the visibilityTimeout timeout has been reached. Also the retry count in increased by one.</p>
     * <p>Checks also the expiration date and removed the messages, which are older than the max retention period.</>
     */
    void ResetMessages();

    /**
     * Check the retention period of messages.
     *
     * <p>Deletes all message which are older than the retention period. Rge default retention period is 14 days, but can ve change on a per queue level.</p>
     */
    void MessageRetention();

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
    Database::ModuleDatabase &_serviceDatabase;

    /**
     * S3 module
     */
    Database::SQSDatabase& _sqsDatabase;

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

#endif // AWSMOCK_SERVICE_SQS_SERVER_H
