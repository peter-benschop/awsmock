//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVER_GATEWAYSERVER_H
#define AWSMOCK_SERVER_GATEWAYSERVER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/dto/lambda/InvocationNotification.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/service/S3Service.h>
#include <awsmock/service/AbstractWorker.h>
#include <awsmock/service/AbstractServer.h>
#include <awsmock/service/GatewayRouter.h>
#include <awsmock/service/LambdaExecutor.h>
#include <awsmock/service/LambdaCreator.h>
#include <awsmock/service/LambdaExecutor.h>
#include <awsmock/service/LambdaMonitoring.h>
#include <awsmock/service/LambdaHandlerFactory.h>

#define GATEWAY_DEFAULT_HOST "localhost"
#define GATEWAY_MAX_QUEUE 250
#define GATEWAY_MAX_THREADS 50
#define GATEWAY_TIMEOUT 900

namespace AwsMock::Service {

  class GatewayServer : public AbstractServer {

  public:

    /**
     * Constructor
     *
     * @param configuration aws-mock configuration
     * @param metricService aws-mock monitoring
     */
    explicit GatewayServer(Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Destructor
     */
    ~GatewayServer() override;

    /**
     * Main method
     */
    void MainLoop() override;

    /**
     * Stop monitoring manager
     */
    void StopMonitoringServer();

  private:

    /**
     * Start monitoring manager
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
     * Metric service
     */
    Core::MetricService &_metricService;

    /**
     * Service database
     */
    std::unique_ptr<Database::ModuleDatabase> _serviceDatabase;

    /**
     * Running flag
     */
    bool _running;

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
     * HTTP max concurrent connection
     */
    int _maxThreads;

    /**
     * HTTP request timeout
     */
    int _requestTimeout;

    /**
     * Gateway router
     */
    std::shared_ptr<Service::GatewayRouter> _router = std::make_shared<Service::GatewayRouter>(_configuration, _metricService);
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVER_GATEWAYSERVER_H
