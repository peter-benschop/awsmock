//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/dynamodb/DynamoDbWorker.h>

namespace AwsMock::Service {

    DynamoDbWorker::DynamoDbWorker(int timeout) : Core::Timer("dynamodb-worker", timeout) {
    }

    void DynamoDbWorker::Initialize() {

        // DynamoDB docker host, port
        _dockerHost = Core::Configuration::instance().getString("awsmock.dynamodb.host");
        _dockerPort = Core::Configuration::instance().getInt("awsmock.dynamodb.port");

        // Region
        _region = Core::Configuration::instance().getString("awsmock.region");

        // Database
        //SynchronizeTables();
        log_debug << "DynamoDbWorker initialized";
    }

    void DynamoDbWorker::Run() {
        //SynchronizeTables();
    }

    void DynamoDbWorker::Shutdown() {}

    // TODO: Fix authorization
    [[maybe_unused]] void DynamoDbWorker::SynchronizeTables() {

        Core::ExecResult result = Core::SystemUtils::Exec("aws dynamodb list-tables --endpoint http://" + _dockerHost + ":" + std::to_string(_dockerPort));
        Dto::DynamoDb::ListTableResponse listTableResponse;
        listTableResponse.FromJson(result.output, {});

        for (const auto &tableName: listTableResponse.tableNames) {
            Core::ExecResult describeResult = Core::SystemUtils::Exec("aws dynamodb describe-table --table-name " + tableName + " --endpoint http://" + _dockerHost + ":" + std::to_string(_dockerPort));
            Dto::DynamoDb::DescribeTableResponse describeTableResponse;
            describeTableResponse.FromJson(describeResult.output, {});

            Database::Entity::DynamoDb::Table table = {.region = describeTableResponse.region, .name = describeTableResponse.tableName, .status = Dto::DynamoDb::TableStatusTypeToString(describeTableResponse.tableStatus), .attributes = describeTableResponse.attributes, .keySchemas = describeTableResponse.keySchemas};
            _dynamoDbDatabase.CreateOrUpdateTable(table);
        }
        log_trace << "DynamoDB synchronized";
    }

}// namespace AwsMock::Service