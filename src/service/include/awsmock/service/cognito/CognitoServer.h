//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITO_SERVER_H
#define AWSMOCK_SERVICE_COGNITO_SERVER_H

// Poco includes
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/repository/CognitoDatabase.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/service/cognito/CognitoHandlerFactory.h>
#include <awsmock/service/cognito/CognitoMonitoring.h>
#include <awsmock/service/common/AbstractServer.h>

#define COGNITO_DEFAULT_PORT 9505
#define COGNITO_DEFAULT_HOST "localhost"
#define COGNITO_DEFAULT_QUEUE_SIZE 250
#define COGNITO_DEFAULT_MAX_THREADS 50
#define COGNITO_DEFAULT_TIMEOUT 900
#define COGNITO_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    /**
     * @brief Cognito module server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CognitoServer : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit CognitoServer(Core::Configuration &configuration);

        /**
         * Initialization
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
         * HTTP manager instance
         */
        std::shared_ptr<Poco::Net::HTTPServer> _httpServer;

        /**
         * Service database
         */
        Database::ModuleDatabase &_moduleDatabase;

        /**
         * Cognito database
         */
        Database::CognitoDatabase &_cognitoDatabase;

        /**
         * Cognito monitoring
         */
        std::shared_ptr<CognitoMonitoring> _cognitoMonitoring;

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
         * Data directory
         */
        std::string _dataDir;

        /**
         * AWS region
         */
        std::string _region;

        /**
         * AWS account ID
         */
        std::string _accountId;

        /**
         * AWS client ID
         */
        std::string _clientId;

        /**
         * AWS user
         */
        std::string _user;

        /**
         * Cognito module name
         */
        std::string _module;

        /**
         * Monitoring period
         */
        int _monitoringPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_COGNITO_SERVER_H
