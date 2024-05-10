//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_SECRETSMANAGER_SERVER_H
#define AWSMOCK_SERVICE_SECRETSMANAGER_SERVER_H

// C++ standard includes
#include <chrono>
#include <string>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/secretsmanager/SecretsManagerHandlerFactory.h>
#include <awsmock/service/secretsmanager/SecretsManagerMonitoring.h>

#define SECRETSMANAGER_DEFAULT_PORT 9507
#define SECRETSMANAGER_DEFAULT_HOST "localhost"
#define SECRETSMANAGER_DEFAULT_QUEUE_LENGTH 250
#define SECRETSMANAGER_DEFAULT_THREADS 50
#define SECRETSMANAGER_DEFAULT_TIMEOUT 120
#define SECRETSMANAGER_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    /**
     * Secret manager server.
     *
     * <p>
     * Default endpoint is localhost:9507. The server supports 50 concurrent threads and support are queue length of 250.
     * </p>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SecretsManagerServer : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param configuration aws-mock configuration
         */
        explicit SecretsManagerServer(Core::Configuration &configuration);

        /**
         * Timer initialization
         */
        void Initialize() override;

        /**
         * Main method
         */
        void Run() override;

        /**
         * Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * Module database
         */
        Database::ModuleDatabase &_moduleDatabase;

        /**
         * Monitoring
         */
        std::shared_ptr<SecretsManagerMonitoring> _secretsManagerMonitoring;

        /**
         * AWS region
         */
        std::string _region;

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
         * HTTP max concurrent connections
         */
        int _maxThreads;

        /**
         * HTTP request timeout in seconds
         */
        int _requestTimeout;

        /**
         * Monitoring period
         */
        int _monitoringPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SECRETSMANAGER_SERVER_H
