//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_S3_SERVER_H
#define AWSMOCK_SERVICE_S3_SERVER_H

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/Timer.h>
#include <awsmock/core/ThreadPool.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/common/AbstractWorker.h>
#include <awsmock/service/s3/S3HandlerFactory.h>

#define S3_DEFAULT_PORT 9500
#define S3_DEFAULT_HOST "localhost"
#define S3_DEFAULT_QUEUE_SIZE 250
#define S3_DEFAULT_MAX_THREADS 50
#define S3_DEFAULT_TIMEOUT 900

namespace AwsMock::Service {

  /**
   * S3 server
   *
   * <p>
   * Default port is 9500.
   * </p>
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class S3Server : public AbstractServer, public AbstractWorker {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService monitoring module
     */
    explicit S3Server(Core::Configuration &configuration, Core::MetricService &metricService);

    /**
     * Timer initialization
     */
    void Initialize() override;

    /**
     * Timer main method
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
     * Rest port
     */
    int _port;

    /**
     * Rest host
     */
    std::string _host;

    /**
    * Application configuration
    */
    Core::Configuration &_configuration;

    /**
     * Metric module
     */
    Core::MetricService &_metricService;

    /**
     * S3 database
     */
    Database::S3Database &_s3Database;

    /**
     * HTTP manager instance
     */
    std::shared_ptr<Poco::Net::HTTPServer> _httpServer;

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
     * Data directory
     */
    std::string _dataDir;

    /**
     * S3 module name
     */
    std::string _module;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_S3SERVER_H
