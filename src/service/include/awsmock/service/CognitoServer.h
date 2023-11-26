//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITOSERVER_H
#define AWSMOCK_SERVICE_COGNITOSERVER_H

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/ThreadPool.h>
#include <awsmock/repository/CognitoDatabase.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/service/AbstractServer.h>
#include <awsmock/service/AbstractWorker.h>
#include <awsmock/service/CognitoMonitoring.h>
#include <awsmock/service/CognitoHandlerFactory.h>

#define COGNITO_DEFAULT_PORT 9500
#define COGNITO_DEFAULT_HOST "localhost"
#define COGNITO_DEFAULT_QUEUE_SIZE 250
#define COGNITO_DEFAULT_MAX_THREADS 50
#define COGNITO_DEFAULT_TIMEOUT 900

namespace AwsMock::Service {

  /**
   * Cognito module
   */
  class CognitoServer : public AbstractServer, public AbstractWorker {

  public:
    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService monitoring module
     */
    explicit CognitoServer(Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Destructor
     */
    ~CognitoServer() override;

    /**
     * Thread main method
     */
    void MainLoop() override;

  private:

    /**
     * Start the monitoring module.
     */
    void StartMonitoringServer();

    /**
     * Stop the monitoring module.
     */
    void StopMonitoringServer();

    /**
     * Update metric counters
     */
    void UpdateCounters();

    /**
     * Rest port
     */
    int _port;

    /**
     * Rest host
     */
    std::string _host;

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
    * Application configuration
    */
    Core::Configuration &_configuration;

    /**
     * Metric module
     */
    Core::MetricService &_metricService;

    /**
     * HTTP manager instance
     */
    std::shared_ptr<Poco::Net::HTTPServer> _httpServer;

    /**
     * Service database
     */
    std::unique_ptr<Database::ModuleDatabase> _moduleDatabase;

    /**
     * S3 database
     */
    std::unique_ptr<Database::CognitoDatabase> _cognitoDatabase;

    /**
     * HTTP max message queue length
     */
    int _maxQueueLength;

    /**
     * HTTP max concurrent connection
     */
    int _maxThreads;

    /**
     * HTTP request timeout in seconds
     */
    int _requestTimeout;

    /**
     * Sleeping period in ms
     */
    int _period;

    /**
     * Running flag
     */
    bool _running;

    /**
     * Data directory
     */
    std::string _dataDir;

    /**
     * AWS region
     */
    std::string _region;

    /**
     * AWS account ID
     */
    std::string _accountId;

    /**
     * AWS client ID
     */
    std::string _clientId;

    /**
     * AWS user
     */
    std::string _user;

    /**
     * S3 module name
     */
    std::string _module;

    /**
     * Thread pool
     */
    AwsMock::Core::ThreadPool<CognitoMonitoring> _threadPool;

  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_COGNITOSERVER_H
