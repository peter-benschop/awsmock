//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_SQS_MONITORING_H
#define AWSMOCK_SERVICE_SQS_MONITORING_H

// AwsMock includes
#include "awsmock/service/monitoring/MetricDefinition.h"
#include "awsmock/service/monitoring/MetricService.h"
#include <awsmock/core/Timer.h>
#include <awsmock/repository/SQSDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief SQS monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSMonitoring {

      public:

        /**
         * @brief Constructor
         */
        explicit SQSMonitoring() = default;

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

      private:

        /**
         * Metric service
         */
        Monitoring::MetricService &_metricService = Monitoring::MetricService::instance();

        /**
         * Database connection
         */
        Database::SQSDatabase &_sqsDatabase = Database::SQSDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SQS_MONITORING_H
