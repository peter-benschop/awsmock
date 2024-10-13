//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_COGNITO_MONITORING_H
#define AWSMOCK_SERVICE_COGNITO_MONITORING_H

// AwsMock includes
#include <awsmock/repository/CognitoDatabase.h>
#include <awsmock/service/monitoring/MetricDefinition.h>
#include <awsmock/service/monitoring/MetricService.h>

namespace AwsMock::Service {

    /**
     * @brief Cognito monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CognitoMonitoring {

      public:

        /**
         * @brief Constructor
         */
        explicit CognitoMonitoring() = default;

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
        Database::CognitoDatabase &_cognitoDatabase = Database::CognitoDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_COGNITO_MONITORING_H
