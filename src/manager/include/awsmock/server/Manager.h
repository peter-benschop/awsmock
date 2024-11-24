//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_MANAGER_H
#define AWSMOCK_MANAGER_H


// AwsMock includes
#include <awsmock/service/gateway/GatewayServer.h>
#include <awsmock/service/module/ModuleMap.h>
#include <awsmock/service/monitoring/MonitoringServer.h>

#define DEFAULT_MONGO_DBNAME "awsmock"
#define DEFAULT_MONGO_DBUSER "root"
#define DEFAULT_MONGO_DBPWD "password"
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
        void Initialize();

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
         * @brief Initialize database
         */
        static void InitializeDatabase();

        /**
         * Thread group
         */
        boost::thread_group _threadGroup;
    };

}// namespace AwsMock::Manager

#endif//AWSMOCK_MANAGER_H
