//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_SNS_MONITORING_H
#define AWSMOCK_SERVICE_SNS_MONITORING_H

// AwsMock includes
#include "awsmock/service/monitoring/MetricDefinition.h"
#include "awsmock/service/monitoring/MetricService.h"
#include <awsmock/core/Timer.h>
#include <awsmock/repository/SNSDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief SNS monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SNSMonitoring {

      public:

        /**
         * Constructor
         */
        explicit SNSMonitoring() = default;

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
        Database::SNSDatabase &_snsDatabase = Database::SNSDatabase::instance();

        /**
         * Period
         */
        int _period{};
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SNS_MONITORING_H
