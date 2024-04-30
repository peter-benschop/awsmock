//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_SNS_MONITORING_H
#define AWSMOCK_SERVICE_SNS_MONITORING_H

// AwsMock includes
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/Timer.h>
#include <awsmock/repository/SNSDatabase.h>

namespace AwsMock::Service {

    /**
     * SNS monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SNSMonitoring : public Core::Timer {

      public:

        /**
         * Constructor
         */
        explicit SNSMonitoring(int timeout) : Core::Timer("sns-monitoring", timeout) {}

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
        Database::SNSDatabase &_snsDatabase = Database::SNSDatabase::instance();

        /**
         * Period
         */
        int _period{};
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SNS_MONITORING_H
