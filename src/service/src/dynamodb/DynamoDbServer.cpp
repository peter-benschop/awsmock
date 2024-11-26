//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/service/dynamodb/DynamoDbServer.h>

namespace AwsMock::Service {
    DynamoDbServer::DynamoDbServer(Core::PeriodicScheduler &scheduler) : AbstractServer("dynamodb"),
                                                                         _containerService(ContainerService::instance()),
                                                                         _dynamoDbDatabase(
                                                                                 Database::DynamoDbDatabase::instance()),
                                                                         _metricService(
                                                                                 Monitoring::MetricService::instance()) {
        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _workerPeriod = configuration.GetValueInt("awsmock.modules.dynamodb.worker.period");
        _monitoringPeriod = configuration.GetValueInt("awsmock.modules.dynamodb.monitoring.period");
        _containerHost = configuration.GetValueString("awsmock.modules.dynamodb.container.host");
        _containerPort = configuration.GetValueInt("awsmock.modules.dynamodb.container.port");
        log_debug << "DynamoDB docker endpoint: " << _containerHost << ":" << _containerPort;

        // Check module active
        if (!IsActive("dynamodb")) {
            log_info << "DynamoDb module inactive";
            return;
        }
        log_info << "DynamoDb server started";

        // Start DynamoDb docker image
        StartLocalDynamoDb();

        // Start DynamoDB monitoring update counters
        //scheduler.AddTask("monitoring-dynamodb-counters", [this] { this->UpdateCounter(); }, _monitoringPeriod);

        // Start synchronizing tables
        //scheduler.AddTask("dynamodb-sync-tables", [this] { this->SynchronizeTables(); }, _workerPeriod);

        // Set running
        SetRunning();
    }

    void DynamoDbServer::CleanupContainers() const {
        _containerService.PruneContainers();
        log_debug << "Docker containers cleaned up";
    }

    void DynamoDbServer::StartLocalDynamoDb() const {
        log_debug << "Starting DynamoDB docker image";

        // Check docker image
        if (!_containerService.ImageExists(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG)) {
            _containerService.BuildImage(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG, DYNAMODB_DOCKER_FILE);
        }

        // Check container image
        if (!_containerService.ContainerExists(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG)) {
            _containerService.CreateContainer(DYNAMODB_DOCKER_IMAGE,
                                              DYNAMODB_DOCKER_TAG,
                                              _containerPort,
                                              _containerPort);
        }

        // Start docker container, in case it is not already running.
        if (const Dto::Docker::Container container = _containerService.GetFirstContainerByImageName(
                    DYNAMODB_DOCKER_IMAGE,
                    DYNAMODB_DOCKER_TAG);
            container.state != "running") {
            _containerService.StartDockerContainer(container.id);
            log_info << "Docker containers for DynamoDB started";
        } else {
            log_info << "Docker containers for DynamoDB already running";
        }
    }

    void DynamoDbServer::StopLocalDynamoDb() const {
        log_debug << "Starting DynamoDB docker image";

        // Check docker image
        if (!_containerService.ImageExists(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG)) {
            throw Core::ServiceException("Image does not exist",
                                         Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        }

        // Check container image
        if (!_containerService.ContainerExists(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG)) {
            throw Core::ServiceException("Container does not exist",
                                         Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        }

        // Stop docker container, in case it is running.
        if (const Dto::Docker::Container container = _containerService.GetFirstContainerByImageName(
                    DYNAMODB_DOCKER_IMAGE,
                    DYNAMODB_DOCKER_TAG);
            container.state == "running") {
            _containerService.StopContainer(container);
            log_info << "Docker containers for DynamoDB stopped";
        } else {
            log_info << "Docker containers for DynamoDB not running";
        }
    }

    void DynamoDbServer::SynchronizeTables() const {
        // Get the list of tables from DynamoDB
        auto [status, output] = Core::SystemUtils::Exec(
                "aws dynamodb list-tables --endpoint http://" + _containerHost + ":" + std::to_string(_containerPort));
        Dto::DynamoDb::ListTableResponse listTableResponse;
        listTableResponse.FromJson(output, {});

        if (!listTableResponse.tableNames.empty()) {
            for (const auto &tableName: listTableResponse.tableNames) {
                auto [status, output] = Core::SystemUtils::Exec(
                        "aws dynamodb describe-table --table-name " + tableName + " --endpoint http://" + _containerHost +
                        ":" + std::to_string(_containerPort));
                Dto::DynamoDb::DescribeTableResponse describeTableResponse;
                describeTableResponse.FromJson(output, {});

                Database::Entity::DynamoDb::Table table = {
                        .region = describeTableResponse.region,
                        .name = describeTableResponse.tableName,
                        .status = Dto::DynamoDb::TableStatusTypeToString(describeTableResponse.tableStatus),
                        .attributes = describeTableResponse.attributes,
                        .keySchemas = describeTableResponse.keySchemas};
                _dynamoDbDatabase.CreateOrUpdateTable(table);
            }
        } else {
            _dynamoDbDatabase.DeleteAllTables();
        }
        log_debug << "DynamoDB synchronized";
    }

    void DynamoDbServer::UpdateCounter() const {
        log_trace << "Dynamodb monitoring starting";

        const long tables = _dynamoDbDatabase.CountTables();
        const long items = _dynamoDbDatabase.CountItems();
        _metricService.SetGauge(DYNAMODB_TABLE_COUNT, static_cast<double>(tables));
        _metricService.SetGauge(DYNAMODB_ITEM_COUNT, static_cast<double>(items));

        log_trace << "DynamoDb monitoring finished";
    }
}// namespace AwsMock::Service
