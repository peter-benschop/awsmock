//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_SERVICE_KMS_SERVER_H
#define AWSMOCK_SERVICE_KMS_SERVER_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/kms/KMSHandlerFactory.h>
#include <awsmock/service/kms/KMSMonitoring.h>
#include <awsmock/service/kms/KMSWorker.h>

#define KMS_DEFAULT_PORT 9502
#define KMS_DEFAULT_HOST "localhost"
#define KMS_DEFAULT_QUEUE_LENGTH 250
#define KMS_DEFAULT_THREADS 50
#define KMS_DEFAULT_TIMEOUT 120
#define KMS_DEFAULT_WORKER_PERIOD 3600
#define KMS_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    /**
     * KMS server thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class KMSServer : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param configuration aws-mock configuration
         */
        explicit KMSServer(Core::Configuration &configuration);

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
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * KMS database
         */
        Database::KMSDatabase &_kmsDatabase;

        /**
         * SNS monitoring
         */
        std::shared_ptr<KMSMonitoring> _kmsMonitoring;

        /**
         * SNS worker
         */
        std::shared_ptr<KMSWorker> _kmsWorker;

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
