//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_COGNITO_MONITORING_H
#define AWSMOCK_SERVICE_COGNITO_MONITORING_H

// AwsMock includes
#include <awsmock/core/JTimer.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/repository/CognitoDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief Cognito monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CognitoMonitoring : public Core::JTimer {

      public:

        /**
         * Constructor
         */
        explicit CognitoMonitoring(int timeout) : Core::JTimer("cognito-monitoring", timeout) {}

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
        Database::CognitoDatabase &_cognitoDatabase = Database::CognitoDatabase::instance();

        /**
         * Period
         */
        int _period{};
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_COGNITO_MONITORING_H
