//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_SSM_MONITORING_H
#define AWSMOCK_SERVICE_SSM_MONITORING_H

// AwsMock includes
#include <awsmock/core/Timer.h>
#include <awsmock/monitoring/MetricDefinition.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/repository/SSMDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief SSM monitoring thread
     *
     * @par
     * The SSM monitoring is 'self-starting', which means the constructor start itself as a background process.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SSMMonitoring : public Core::Timer {

      public:

        /**
         * Constructor
         */
        explicit SSMMonitoring(int timeout);

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
        Database::SSMDatabase &_ssmDatabase = Database::SSMDatabase::instance();

        /**
         * Period
         */
        int _period{};
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_MONITORING_H
