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
#include <awsmock/core/scheduler/PeriodicScheduler.h>
#include <awsmock/core/scheduler/PeriodicTask.h>
#include <awsmock/repository/CognitoDatabase.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/service/cognito/CognitoMonitoring.h>
#include <awsmock/service/common/AbstractServer.h>

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
         */
        explicit CognitoServer();

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
         * Cognito monitoring
         */
        CognitoMonitoring _cognitoMonitoring;

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
