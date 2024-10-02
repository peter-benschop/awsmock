//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_KMS_MONITORING_H
#define AWSMOCK_SERVICE_KMS_MONITORING_H

// AwsMock includes
#include <awsmock/core/Timer.h>
#include <awsmock/monitoring/MetricDefinition.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/repository/KMSDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief KMS monitoring thread
     *
     * @par
     * The KMS monitoring is 'self-starting', which means the constructor start itself as a background process.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class KMSMonitoring : public Core::Timer {

      public:

        /**
         * Constructor
         */
        explicit KMSMonitoring(int timeout);

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
        Monitoring::MetricService &_metricService = Monitoring::MetricService::instance();

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
