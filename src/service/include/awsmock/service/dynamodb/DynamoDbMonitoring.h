//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_DYNAMODB_MONITORING_H
#define AWSMOCK_SERVICE_DYNAMODB_MONITORING_H

// AwsMock includes
#include <awsmock/core/Timer.h>
#include <awsmock/monitoring/MetricDefinition.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/repository/DynamoDbDatabase.h>

namespace AwsMock::Service {

    /**
     * @brief DynamoDB monitoring thread
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DynamoDbMonitoring : public Core::Timer {

      public:

        /**
         * Constructor
         */
        explicit DynamoDbMonitoring(int timeout);

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
        Database::DynamoDbDatabase &_dynamoDbDatabase = Database::DynamoDbDatabase::instance();

        /**
         * Period
         */
        int _period{};
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_DYNAMODB_MONITORING_H
