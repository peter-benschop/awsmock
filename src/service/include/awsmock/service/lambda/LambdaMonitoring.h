//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_LAMBDA_MONITORING_H
#define AWSMOCK_SERVICE_LAMBDA_MONITORING_H

// AwsMock includes
#include "awsmock/service/monitoring/MetricDefinition.h"
#include "awsmock/service/monitoring/MetricService.h"
#include <awsmock/core/Timer.h>
#include <awsmock/repository/LambdaDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief Lambda monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class LambdaMonitoring {

      public:

        /**
         * Constructor
         */
        explicit LambdaMonitoring() = default;

        /**
         * Update counters
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
        Database::LambdaDatabase &_lambdaDatabase = Database::LambdaDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_LAMBDA_MONITORING_H
