//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/service/dynamodb/DynamoDbServer.h>

namespace AwsMock::Service {
    DynamoDbServer::DynamoDbServer(Core::PeriodicScheduler &scheduler) : AbstractServer("dynamodb"), _containerService(ContainerService::instance()), _dynamoDbDatabase(Database::DynamoDbDatabase::instance()), _metricService(Monitoring::MetricService::instance()) {
        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _workerPeriod = configuration.GetValueInt("awsmock.modules.dynamodb.worker.period");
        _monitoringPeriod = configuration.GetValueInt("awsmock.modules.dynamodb.monitoring.period");
        _containerName = configuration.GetValueString("awsmock.modules.dynamodb.container.name");
        _containerHost = configuration.GetValueString("awsmock.modules.dynamodb.container.host");
        _containerPort = configuration.GetValueInt("awsmock.modules.dynamodb.container.port");
        _imageName = configuration.GetValueString("awsmock.modules.dynamodb.container.image-name");
        _imageTag = configuration.GetValueString("awsmock.modules.dynamodb.container.image-tag");
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
        scheduler.AddTask("monitoring-dynamodb-counters", [this] { this->UpdateCounter(); }, _monitoringPeriod);

        // Start synchronizing tables
        scheduler.AddTask("dynamodb-sync-tables", [this] { this->SynchronizeTables(); }, _workerPeriod);

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
        if (!_containerService.ImageExists(_imageName, _imageTag)) {
            const std::string output = _containerService.BuildImage(_imageName, _imageTag, DYNAMODB_DOCKER_FILE);
            log_trace << "Image " << _imageName << " output: " << output;
        }

        // Check container image
        if (!_containerService.ContainerExistsByName(_containerName)) {
            const Dto::Docker::CreateContainerResponse response = _containerService.CreateContainer(_imageName, _imageTag, _containerName, _containerPort, _containerPort);
            log_trace << "CreateContainer, containerName: " << _containerName << " id: " << response.id;
        }

        // Start docker container, in case it is not already running.
        if (const Dto::Docker::Container container = _containerService.GetFirstContainerByImageName(_imageName, _imageTag);
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
        if (!_containerService.ImageExists(_imageName, _imageTag)) {
            log_error << "Image " << _imageName << " does not exist";
            throw Core::ServiceException("Image does not exist");
        }

        // Check container image
        if (!_containerService.ContainerExists(_imageName, _imageTag)) {
            log_error << "Container " << _imageName << " does not exist";
            throw Core::ServiceException("Container does not exist");
        }

        // Stop docker container, in case it is running.
        if (const Dto::Docker::Container container = _containerService.GetFirstContainerByImageName(_imageName, _imageTag);
            container.state == "running") {
            _containerService.StopContainer(container);
            log_info << "Docker containers for DynamoDB stopped";
        } else {
            log_info << "Docker containers for DynamoDB not running";
        }
    }

    void DynamoDbServer::SynchronizeTables() const {

        try {
            // Get the list of tables from DynamoDB
            auto [status, output] = Core::SystemUtils::Exec("aws dynamodb list-tables --endpoint http://" + _containerHost + ":" + std::to_string(_containerPort));
            Dto::DynamoDb::ListTableResponse listTableResponse;
            listTableResponse.FromJson(output, {});

            if (!listTableResponse.tableNames.empty()) {
                for (const auto &tableName: listTableResponse.tableNames) {
                    auto [status, output] = Core::SystemUtils::Exec("aws dynamodb describe-table --table-name " + tableName + " --endpoint http://" + _containerHost + ":" + std::to_string(_containerPort));
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

        } catch (Core::JsonException &exc) {
            log_error << exc.what();
        }
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
