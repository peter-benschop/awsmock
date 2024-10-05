//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITO_SERVER_H
#define AWSMOCK_SERVICE_COGNITO_SERVER_H

// Boost includes
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/repository/CognitoDatabase.h>
#include <awsmock/repository/ModuleDatabase.h>
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
         * @brief Constructor
         *
         * @param pool global thread pool
         */
        explicit CognitoServer(boost::asio::thread_pool &pool);

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
         * Cognito monitoring
         */
        std::shared_ptr<CognitoMonitoring> _cognitoMonitoring;

        /**
         * Global thread pool
         */
        boost::asio::thread_pool &_pool;

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
