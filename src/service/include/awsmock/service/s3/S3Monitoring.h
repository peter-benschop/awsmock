//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_S3_MONITORING_H
#define AWSMOCK_SERVICE_S3_MONITORING_H

// AwsMock includes
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/Timer.h>
#include <awsmock/repository/S3Database.h>

namespace AwsMock::Service {

    /**
     * S3 monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3Monitoring : public Core::Timer {

      public:

        /**
         * Constructor
         */
        explicit S3Monitoring(int timeout) : Core::Timer("s3-monitoring", timeout) {}

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
        Database::S3Database &_s3Database = Database::S3Database::instance();

        /**
         * Period
         */
        int _period{};
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_S3_MONITORING_H
