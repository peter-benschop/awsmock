//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_SERVICE_SSM_SERVER_H
#define AWSMOCK_SERVICE_SSM_SERVER_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/ssm/SSMMonitoring.h>
#include <awsmock/service/ssm/SSMWorker.h>

#define SSM_DEFAULT_PORT 9509
#define SSM_DEFAULT_HOST "localhost"
#define SSM_DEFAULT_QUEUE_LENGTH 250
#define SSM_DEFAULT_THREADS 50
#define SSM_DEFAULT_TIMEOUT 120
#define SSM_DEFAULT_WORKER_PERIOD 3600
#define SSM_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    /**
     * @brief SSM HTTP server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SSMServer : public AbstractServer {

      public:

        /**
         * @brief Constructor
         *
         * @param configuration aws-mock configuration
         */
        explicit SSMServer(Core::Configuration &configuration);

        /**
         * @brief Initialization
         */
        void Initialize() override;

        /**
         * @brief Main method
         */
        void Run() override;

        /**
         * @brief Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * ssm database
         */
        Database::SSMDatabase &_ssmDatabase;

        /**
         * SNS monitoring
         */
        std::shared_ptr<SSMMonitoring> _ssmMonitoring;

        /**
         * SNS worker
         */
        std::shared_ptr<SSMWorker> _ssmWorker;

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
         * SNS server period
         *
         * <p>
         * Used for the background threads (cleanup, reset, retention, etc.)
         * </p>
         */
        int _workerPeriod;

        /**
         * SNS monitoring period
         */
        int _monitoringPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_SERVER_H
