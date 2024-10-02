//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_TRANSFER_MONITORING_H
#define AWSMOCK_SERVICE_TRANSFER_MONITORING_H

// AwsMock includes
#include <awsmock/core/Timer.h>
#include <awsmock/monitoring/MetricDefinition.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/repository/TransferDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief Transfer family monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class TransferMonitoring : public Core::Timer {

      public:

        /**
         * @brief Constructor
         *
         * @param timeout monitoring period in seconds.
         */
        explicit TransferMonitoring(int timeout) : Core::Timer("transfer-monitoring", timeout) {}

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
         * @brief Update counters
         */
        void UpdateCounter();

        /**
         * @brief Metric service
         */
        Monitoring::MetricService &_metricService = Monitoring::MetricService::instance();

        /**
         * @brief Database connection
         */
        Database::TransferDatabase &_transferDatabase = Database::TransferDatabase::instance();

        /**
         * @brief Period
         */
        int _period{};
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_TRANSFER_MONITORING_H
