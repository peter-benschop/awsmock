//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_CONTROLLER_RESTSERVICE_H
#define AWSMOCK_CONTROLLER_RESTSERVICE_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServer.h"

// Libri includes
#include "awsmock/core/Configuration.h"

#define DEFAULT_PORT 4567
#define DEFAULT_HOST "localhost"

namespace AwsMock {

    /**
     * General REST service
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
       * Return singleton instance
       *
       * @return singleton instance.
       */
      /*static RestService &instance() {
          static Poco::SingletonHolder<RestService> _restServerInstance;
          return *_restServerInstance.get();
      }*/

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
      Poco::Net::HTTPRequestHandlerFactory *getRouter();

      /**
       * Sets the REST URL router
       *
       * @param router HTTP request router.
       */
      void setRouter(Poco::Net::HTTPRequestHandlerFactory *router);

      /**
       * Start the restfull service.
       *
       * The router has to be defined before the HTTP server is started.
       */
      void start();

      /**
       * Start with port and router.
       *
       * @param router router to use
       * @param port port to use (default: 9100)
       */
      void start(Poco::Net::HTTPRequestHandlerFactory *router, int port = DEFAULT_PORT);

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
      * Logger
      */
      Core::Configuration &_configuration;

      /**
       * Rest port
       */
      int _port;

      /**
       * Rest host
       */
      std::string _host;

      /**
       * REST router
       */
      Poco::Net::HTTPRequestHandlerFactory *_router;

      /**
       * HTTP server instance
       */
      Poco::Net::HTTPServer *httpServer;
    };
} // namespace AwsMock

#endif //AWSMOCK_CONTROLLER_RESTSERVICE_H
