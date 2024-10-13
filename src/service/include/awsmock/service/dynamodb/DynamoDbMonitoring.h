//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_DYNAMODB_MONITORING_H
#define AWSMOCK_SERVICE_DYNAMODB_MONITORING_H

// AwsMock includes
#include <awsmock/repository/DynamoDbDatabase.h>
#include <awsmock/service/monitoring/MetricDefinition.h>
#include <awsmock/service/monitoring/MetricService.h>

namespace AwsMock::Service {

    /**
     * @brief DynamoDB monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DynamoDbMonitoring {

      public:

        /**
         * Constructor
         */
        explicit DynamoDbMonitoring() = default;

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
        Database::DynamoDbDatabase &_dynamoDbDatabase = Database::DynamoDbDatabase::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_DYNAMODB_MONITORING_H
