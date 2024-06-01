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
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/core/monitoring/MetricSystemCollector.h>
#include <awsmock/server/Handler.h>
#include <awsmock/server/Listener.h>

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
         * @brief Start the modules.
         *
         * Only the modules are started, which are set to 'active' in the configuration file.
         */
        void StartModules();

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
         * @brief Initialize the logging
         */
        static void InitializeLogging();

        /**
         * @brief Initialize the Prometheus monitoring counters and StartServer the prometheus manager.
         */
        static void InitializeMonitoring();

        /**
         * @brief Initialize database
         */
        static void InitializeDatabase();

        /**
         * @brief Initialize CURL library
         */
        static void InitializeCurl();

        /**
         * Server map
         */
        Service::ServerMap _serverMap;
    };

}// namespace AwsMock::Manager

#endif//AWSMOCK_MANAGER_H
