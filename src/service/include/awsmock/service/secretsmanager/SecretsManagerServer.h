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
#include <awsmock/service/secretsmanager/SecretsManagerHandlerFactory.h>

#define SECRETSMANAGER_DEFAULT_PORT 9507
#define SECRETSMANAGER_DEFAULT_HOST "localhost"
#define SECRETSMANAGER_DEFAULT_QUEUE_LENGTH  250
#define SECRETSMANAGER_DEFAULT_THREADS 50
#define SECRETSMANAGER_DEFAULT_TIMEOUT 120

namespace AwsMock::Service {

  /**
   * Secret manager server.
   *
   * <p>
   * Default endpoint is localhost:9507. The server supports 50 concurrent threads and support are queue length of 250.
   * </p>
   *
   * @author jens.vogt@opitz-consulting.com
   */
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
     * Timer initialization
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
