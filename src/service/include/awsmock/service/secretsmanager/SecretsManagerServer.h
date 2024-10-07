//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_SECRETSMANAGER_SERVER_H
#define AWSMOCK_SERVICE_SECRETSMANAGER_SERVER_H

// C++ standard includes
#include <chrono>
#include <string>

// Boost includes
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/scheduler/PeriodicScheduler.h>
#include <awsmock/core/scheduler/PeriodicTask.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/secretsmanager/SecretsManagerMonitoring.h>

#define SECRETSMANAGER_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    /**
     * @brief Secret manager server.
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
         * @brief Constructor
         */
        explicit SecretsManagerServer();

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
         * Monitoring
         */
        SecretsManagerMonitoring _secretsManagerMonitoring;

        /**
         * Monitoring period
         */
        int _monitoringPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SECRETSMANAGER_SERVER_H
