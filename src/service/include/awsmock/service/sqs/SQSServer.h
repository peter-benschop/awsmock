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
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/monitoring/MetricDefinition.h>
#include <awsmock/service/monitoring/MetricService.h>

#define SQS_DEFAULT_MONITORING_PERIOD 300
#define SQS_DEFAULT_WORKER_PERIOD 30

namespace AwsMock::Service {

    /**
     * @brief SQS module server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSServer : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit SQSServer(Core::PeriodicScheduler &scheduler);

      private:

        /**
         * @brief Adjust queue counters during startup.
         *
         * @par
         * This is only done once per startup, do synchronize the current state of the messages to the queue counters. All following message
         * operations (send, delete, purge etc.) will adjust the queue counters by itself.
         */
        void AdjustCounters();

        /**
         * @brief Reset resources
         *
         * @par
         * Loops over all SQS queues and sets the state to INITIAL in case the visibilityTimeout timeout has been reached. Also the retry count in increased by one.
         *
         * @par
         * Checks also the expiration date and removed the resources, which are older than the max retention period.
         */
        void ResetMessages();

        /**
         * @brief Collect waiting time statistics
         *
         * @par
         * Collects the average waiting time for messages in that queue.
         */
        void CollectWaitingTimeStatistics();

        /**
         * @brief Update counters
         */
        void UpdateCounter();

        /**
         * Metric service
         */
        Monitoring::MetricService &_metricService = Monitoring::MetricService::instance();

        /**
         * SQS database
         */
        Database::SQSDatabase _sqsDatabase;

        /**
         * SQS monitoring period
         */
        int _monitoringPeriod;

        /**
         * SQS reset period
         */
        int _resetPeriod;

        /**
         * SQS adjust counter period
         */
        int _counterPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SQS_SERVER_H
