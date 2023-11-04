//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_ABSTRACTSERVER_H
#define AWSMOCK_SERVICE_ABSTRACTSERVER_H

// C++ standard includes
#include <string>
#include <map>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/Logger.h>
#include <Poco/Task.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerResponse.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/CurlUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/repository/ModuleDatabase.h>

namespace AwsMock::Service {

  class AbstractServer : public Poco::Runnable {

    public:

      /**
       * Constructor
       *
       * @param configuration AwsMock configuration
       * @param name manager name
       */
      explicit AbstractServer(const Core::Configuration &configuration, std::string name);

      /**
       * Checks whether the service is active
       *
       * @param name module name
       */
      bool IsActive(const std::string &name);

      /**
       * Returns the running flag
       */
      bool IsRunning() const;

      /**
       * Main thread methods
       */
      void run() override;

      /**
       * Stop the manager
       */
      void StopServer();

      /**
       * Start the HTTP manager
       *
       * @param maxQueueLength maximal request queue length
       * @param maxThreads maximal number of worker threads
       * @param requestTimeout request timeout in seconds
       * @param host HTTP host name
       * @param port HTTP port
       * @param requestFactory HTTP request factory
       */
      void StartHttpServer(int maxQueueLength, int maxThreads, int requestTimeout, const std::string &host, int port, Poco::Net::HTTPRequestHandlerFactory *requestFactory);

      /**
       * Stops the HTTP manager
       */
      void StopHttpServer();

    protected:

      /**
       * Main loop
       */
      virtual void MainLoop() = 0;

      /**
       * Interruptable sleep
       */
      bool InterruptableSleep(int period);

      /**
       * Shutdown condition
       */
      Poco::Condition _condition;

    private:

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Service name
       */
      std::string _name;

      /**
       * Service database
       */
      std::unique_ptr<Database::ModuleDatabase> _serviceDatabase;

      /**
       * Shutdown mutex
       */
      Poco::Mutex _mutex;

      /**
       * Running flag
       */
      bool _running;

      /**
       * HTTP manager instance
       */
      std::shared_ptr<Poco::Net::HTTPServer> _httpServer;
  };

  /**
   * Server map
   */
  typedef std::map<std::string, Service::AbstractServer*> ServerMap;

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_ABSTRACTSERVER_H
