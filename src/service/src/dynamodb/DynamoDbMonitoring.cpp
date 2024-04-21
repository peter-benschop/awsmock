//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/dynamodb/DynamoDbMonitoring.h>

namespace AwsMock::Service {

    void DynamoDbMonitoring::Initialize() {
        UpdateCounter();
    }

    void DynamoDbMonitoring::Run() {
        UpdateCounter();
    }

    void DynamoDbMonitoring::Shutdown() {}

    void DynamoDbMonitoring::UpdateCounter() {
        long tables = _dynamoDbDatabase.CountTables();
        _metricService.SetGauge(DYNAMODB_TABLE_COUNT, tables);
        log_trace << "DynamoDb update counter finished";
    }
}