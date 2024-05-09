//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_MANAGER_REST_SERVICE_H
#define AWSMOCK_MANAGER_REST_SERVICE_H


// C++ includes
#include <utility>

// Poco includes
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServer.h"

// AwsMock includes
#include <awsmock/controller/Router.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>

#define MANAGER_DEFAULT_PORT 4567
#define MANAGER_DEFAULT_HOST "localhost"
#define MANAGER_MAX_CONNECTIONS 250
#define MANAGER_MAX_THREADS 50

namespace AwsMock {

    /**
     * General REST module
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class RestService {

      public:

        /**
         * Constructor
         */
        explicit RestService();

        /**
         * Sets the REST port.
         *
         * @param port REST port.
         */
        void setPort(int port);

        /**
         * Sets the REST URL router
         *
         * @param router HTTP request router.
         */
        void setRouter(std::unique_ptr<Controller::Router> router);

        /**
         * Start the restfull module.
         *
         * The router has to be defined before the HTTP manager is started.
         */
        void StartServer();

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
         * REST router
         */
        std::unique_ptr<Controller::Router> _router;

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
    };
}// namespace AwsMock

#endif// AWSMOCK_MANAGER_REST_SERVICE_H
