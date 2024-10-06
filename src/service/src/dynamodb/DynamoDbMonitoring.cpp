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
        log_trace << "Dynamodb monitoring starting";

        long tables = _dynamoDbDatabase.CountTables();
        long items = _dynamoDbDatabase.CountItems();
        _metricService.SetGauge(DYNAMODB_TABLE_COUNT, tables);
        _metricService.SetGauge(DYNAMODB_ITEM_COUNT, items);

        log_trace << "DynamoDb monitoring finished";
    }

}// namespace AwsMock::Service