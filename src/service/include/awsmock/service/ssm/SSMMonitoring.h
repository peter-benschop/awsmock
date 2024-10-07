//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_SSM_MONITORING_H
#define AWSMOCK_SERVICE_SSM_MONITORING_H

// AwsMock includes
#include "awsmock/service/monitoring/MetricDefinition.h"
#include "awsmock/service/monitoring/MetricService.h"
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
    class SSMMonitoring {

      public:

        /**
         * @brief Constructor
         */
        explicit SSMMonitoring() = default;

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
        Database::SSMDatabase &_ssmDatabase = Database::SSMDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_MONITORING_H
