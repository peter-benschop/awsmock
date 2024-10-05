//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_MANAGER_H
#define AWSMOCK_MANAGER_H

// C++ includes
#include <string>

// MongoDB includes
#include <mongocxx/instance.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/server/Handler.h>
#include <awsmock/server/Listener.h>
#include <awsmock/service/monitoring/MonitoringServer.h>

#define DEFAULT_MONGO_DBNAME "awsmock"
#define DEFAULT_MONGO_DBUSER "admin"
#define DEFAULT_MONGO_DBPWD "admin"
#define DEFAULT_MONGO_DBHOST "localhost"
#define DEFAULT_MONGO_DBPORT 27017
#define DEFAULT_MONGO_POOL_SIZE 256

namespace AwsMock::Manager {

    /**
     * @brief Main application class for the awsmock manager.
     *
     * The manager is controlling the different services. Services are activated ib the configuration file or via environment variables. Only the activated
     * services are started. The general flow is:
     *   - Process command line parameters
     *   - Read the configuration file and process environment variables
     *   - Start the database (either MongoDB or in-memory database)
     *   - General initializations
     *   - Start the activated services are background threads
     *   - Start the API gateway on port 4566 by default (can be changed in the configuration file)
     *   - Wait for a termination signal
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class Manager {

      public:

        Manager() = default;

        /**
         * @brief Initialization
         */
        static void Initialize();

        /**
         * @brief Stops all currently running modules.
         */
        void StopModules();

        /**
         * @brief Main processing loop.
         */
        void Run();

      private:

        /**
         * @brief Initialize the Prometheus monitoring counters and StartServer the prometheus manager.
         */
        static void InitializeMonitoring();

        /**
         * @brief Initialize database
         */
        static void InitializeDatabase();

        /**
         * Server map
         */
        Service::ServerMap _serverMap;

        /**
         * Thread group
         */
        boost::thread_group _threadGroup;
    };

}// namespace AwsMock::Manager

#endif//AWSMOCK_MANAGER_H
