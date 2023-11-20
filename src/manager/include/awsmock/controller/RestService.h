//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_MANAGER_RESTSERVICE_H
#define AWSMOCK_MANAGER_RESTSERVICE_H

// Poco includes
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServer.h"

// AwsMock includes
#include "awsmock/core/LogStream.h"
#include "awsmock/core/Configuration.h"

#define MANAGER_DEFAULT_PORT 4567
#define MANAGER_DEFAULT_HOST "localhost"
#define MANAGER_MAX_CONNECTIONS 250
#define MANAGER_MAX_THREADS 50

namespace AwsMock {

  /**
   * General REST module
   */
  class RestService {

  public:
    /**
     * Constructor
     *
     * @param configuration application configuration
     */
    explicit RestService(Core::Configuration &configuration);

    /**
     * Destructor
     */
    ~RestService();

    /**
     * Sets the REST port.
     *
     * @param port REST port.
     */
    void setPort(int port);

    /**
     * Returns the current router
     *
     * @return REST URL router
     */
    std::shared_ptr<Poco::Net::HTTPRequestHandlerFactory> getRouter();

    /**
     * Sets the REST URL router
     *
     * @param router HTTP request router.
     */
    void setRouter(std::shared_ptr<Poco::Net::HTTPRequestHandlerFactory> router);

    /**
     * Start the restfull module.
     *
     * The router has to be defined before the HTTP manager is started.
     */
    void StartServer();

    /**
     * Start with port and router.
     *
     * @param router router to use
     * @param port port to use (default: 9100)
     */
    void StartServer(std::shared_ptr<Poco::Net::HTTPRequestHandlerFactory> router, int port = MANAGER_DEFAULT_PORT);

    /**
     * Stop the manager
     */
    void StopServer();

  private:

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
    * Logger
    */
    Core::Configuration &_configuration;

    /**
     * REST router
     */
    std::shared_ptr<Poco::Net::HTTPRequestHandlerFactory> _router = nullptr;

    /**
     * HTTP manager instance
     */
    std::shared_ptr<Poco::Net::HTTPServer> _httpServer = nullptr;

    /**
     * HTTP max message queue length
     */
    int _maxQueueLength;

    /**
     * HTTP max concurrent connection
     */
    int _maxThreads;
  };
} // namespace AwsMock

#endif // AWSMOCK_MANAGER_RESTSERVICE_H
