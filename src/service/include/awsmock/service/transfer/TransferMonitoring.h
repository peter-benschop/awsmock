//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_TRANSFER_MONITORING_H
#define AWSMOCK_SERVICE_TRANSFER_MONITORING_H

// AwsMock includes
#include <awsmock/monitoring/MetricDefinition.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/repository/TransferDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief Transfer family monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class TransferMonitoring {

      public:

        /**
         * @brief Constructor
         *
         * @param timeout monitoring period in seconds.
         */
        explicit TransferMonitoring() = default;

        /**
         * @brief Update counters
         */
        void UpdateCounter();

      private:

        /**
         * @brief Metric service
         */
        Monitoring::MetricService &_metricService = Monitoring::MetricService::instance();

        /**
         * @brief Database connection
         */
        Database::TransferDatabase &_transferDatabase = Database::TransferDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_TRANSFER_MONITORING_H
