//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_S3_MONITORING_H
#define AWSMOCK_SERVICE_S3_MONITORING_H

// AwsMock includes
#include "awsmock/service/monitoring/MetricDefinition.h"
#include "awsmock/service/monitoring/MetricService.h"
#include <awsmock/repository/S3Database.h>

namespace AwsMock::Service {

    /**
     * @brief S3 monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3Monitoring {

      public:

        /**
         * Constructor
         */
        explicit S3Monitoring() = default;

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
        Database::S3Database &_s3Database = Database::S3Database::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_S3_MONITORING_H
