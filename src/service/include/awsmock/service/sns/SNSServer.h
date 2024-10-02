//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_SERVICE_SNS_SERVER_H
#define AWSMOCK_SERVICE_SNS_SERVER_H

// C++ standard includes
#include <string>

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include <awsmock/core/LogStream.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/sns/SNSMonitoring.h>
#include <awsmock/service/sns/SNSWorker.h>

#define SNS_DEFAULT_PORT 9502
#define SNS_DEFAULT_HOST "localhost"
#define SNS_DEFAULT_QUEUE_LENGTH 250
#define SNS_DEFAULT_THREADS 50
#define SNS_DEFAULT_TIMEOUT 120
#define SNS_DEFAULT_WORKER_PERIOD 300
#define SNS_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    /**
     * @brief SNS server thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SNSServer : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param configuration aws-mock configuration
         */
        explicit SNSServer(Core::Configuration &configuration);

        /**
         * Initialization
         */
        void Initialize() override;

      protected:

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
         * SNS database
         */
        Database::SNSDatabase &_snsDatabase;

        /**
         * SNS monitoring
         */
        std::shared_ptr<SNSMonitoring> _snsMonitoring;

        /**
         * SNS worker
         */
        std::shared_ptr<SNSWorker> _snsWorker;

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

#endif// AWSMOCK_SERVICE_SNSSERVER_H
