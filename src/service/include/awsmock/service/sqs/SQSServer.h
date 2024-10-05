//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_SQS_SERVER_H
#define AWSMOCK_SERVICE_SQS_SERVER_H

// C++ standard includes
#include <chrono>
#include <string>

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include <awsmock/core/LogStream.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/sqs/SQSMonitoring.h>
#include <awsmock/service/sqs/SQSWorker.h>

#define SQS_DEFAULT_PORT 9501
#define SQS_DEFAULT_HOST "localhost"
#define SQS_DEFAULT_QUEUE_LENGTH 250
#define SQS_DEFAULT_THREADS 50
#define SQS_DEFAULT_TIMEOUT 120
#define SQS_DEFAULT_MONITORING_PERIOD 300
#define SQS_DEFAULT_WORKER_PERIOD 30

namespace AwsMock::Service {

    /**
     * SQS server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSServer : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param configuration aws-mock configuration
         */
        explicit SQSServer(boost::asio::thread_pool &pool);

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
         * SQS database
         */
        Database::SQSDatabase &_sqsDatabase;

        /**
         * SQS monitoring
         */
        std::shared_ptr<SQSMonitoring> _sqsMonitoring;

        /**
         * SQS worker
         */
        std::shared_ptr<SQSWorker> _sqsWorker;

        /**
         * Global thread pool
         */
        boost::asio::thread_pool &_pool;

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
         * SQS monitoring period
         */
        int _monitoringPeriod;

        /**
         * SQS worker period
         */
        int _workerPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SQS_SERVER_H
