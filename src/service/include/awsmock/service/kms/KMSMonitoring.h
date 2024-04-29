//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_KMS_MONITORING_H
#define AWSMOCK_SERVICE_KMS_MONITORING_H

// AwsMock includes
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/Timer.h>
#include <awsmock/repository/KMSDatabase.h>

namespace AwsMock::Service {

    /**
     * KMS monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class KMSMonitoring : public Core::Timer {

      public:

        /**
         * Constructor
         */
        explicit KMSMonitoring(int timeout) : Core::Timer("kms-monitoring", timeout) {}

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
         * Update counters
         */
        void UpdateCounter();

        /**
         * Metric service
         */
        Core::MetricService &_metricService = Core::MetricService::instance();

        /**
         * Database connection
         */
        Database::KMSDatabase &_kmsDatabase = Database::KMSDatabase::instance();

        /**
         * Period
         */
        int _period{};
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_MONITORING_H
