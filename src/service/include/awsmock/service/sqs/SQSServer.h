//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_SQS_SERVER_H
#define AWSMOCK_SERVICE_SQS_SERVER_H

// C++ standard includes
#include <chrono>
#include <string>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/scheduler/PeriodicScheduler.h>
#include <awsmock/core/scheduler/PeriodicTask.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/sqs/SQSMonitoring.h>
#include <awsmock/service/sqs/SQSWorker.h>

#define SQS_DEFAULT_MONITORING_PERIOD 300
#define SQS_DEFAULT_WORKER_PERIOD 30

namespace AwsMock::Service {

    /**
     * @brief SQS server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSServer : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit SQSServer();

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
         * SQS monitoring
         */
        SQSMonitoring _sqsMonitoring;

        /**
         * SQS worker
         */
        SQSWorker _sqsWorker;

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
