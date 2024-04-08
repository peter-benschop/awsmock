//
// Created by vogje01 on 20/12/2023.
//

#include "awsmock/service/dynamodb/DynamoDbServer.h"

namespace AwsMock::Service {

  DynamoDbServer::DynamoDbServer(Core::Configuration &configuration, Core::MetricService &metricService)
    : AbstractWorker(configuration), AbstractServer(configuration, "dynamodb"), _logger(Poco::Logger::get("DynamoDbServer")), _configuration(configuration), _metricService(metricService), _module("dynamodb"),
      _dynamoDbDatabase(Database::DynamoDbDatabase::instance()) {

    // Get HTTP configuration values
    _region = _configuration.getString("awsmock.region");
    _port = _configuration.getInt("awsmock.service.dynamodb.port", DYNAMODB_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.dynamodb.host", DYNAMODB_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.dynamodb.max.queue", DYNAMODB_DEFAULT_QUEUE);
    _maxThreads = _configuration.getInt("awsmock.service.dynamodb.max.threads", DYNAMODB_DEFAULT_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.dynamodb.timeout", DYNAMODB_DEFAULT_TIMEOUT);

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.dynamodb.period", 10000);
    log_debug_stream(_logger) << "DynamoDB server period: " << _period << std::endl;

    // Docker module
    _dockerService = std::make_unique<Service::DockerService>(_configuration);
    log_debug_stream(_logger) << "DynamoDbServer initialized" << std::endl;

    // Start DynamoDb docker image
    StartLocalDynamoDb();
  }

  DynamoDbServer::~DynamoDbServer() {
    StopServer();
  }

  void DynamoDbServer::MainLoop() {

    // Check module active
    if (!IsActive("dynamodb")) {
      log_info_stream(_logger) << "DynamoDb module inactive" << std::endl;
      return;
    }
    log_info_stream(_logger) << "DynamoDb server started" << std::endl;

    // Start monitoring thread
    StartMonitoringServer();

    // Start HTTP manager
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new DynamoDbRequestHandlerFactory(_configuration, _metricService));

    // Cleanup
    CleanupContainers();

    while (IsRunning()) {

      log_debug_stream(_logger) << "DynamoDb processing started" << std::endl;

      // Wait for timeout or condition
      if (InterruptableSleep(_period)) {
        StopMonitoringServer();
        StopHttpServer();
        StopLocalDynamoDb();
        break;
      }
    }
  }

  void DynamoDbServer::StartMonitoringServer() {
    _threadPool.StartThread(_configuration, _metricService, _condition);
  }

  void DynamoDbServer::StopMonitoringServer() {
    _threadPool.stopAll();
  }

  void DynamoDbServer::CleanupContainers() {
    _dockerService->PruneContainers();
    log_debug_stream(_logger) << "Docker containers cleaned up" << std::endl;
  }

  void DynamoDbServer::StartLocalDynamoDb() {
    log_debug_stream(_logger) << "Starting DynamoDB docker image" << std::endl;

    // Check docker image
    if (!_dockerService->ImageExists(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG)) {
      _dockerService->BuildImage(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG, DYNAMODB_DOCKER_FILE);
    }

    // Check container image
    if (!_dockerService->ContainerExists(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG)) {
      _dockerService->CreateContainer(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG, DYNAMODB_EXTERNAL_PORT, DYNAMODB_INTERNAL_PORT);
    }

    // Get docker container
    Dto::Docker::Container container = _dockerService->GetContainerByName(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG);

    // Start docker container, in case it is not already running.
    if (container.state != "running") {
      _dockerService->StartDockerContainer(container.id);
      log_info_stream(_logger) << "Docker containers for DynamoDB started" << std::endl;
    } else {
      log_warning_stream(_logger) << "Docker containers for DynamoDB already running" << std::endl;
    }

  }

  void DynamoDbServer::StopLocalDynamoDb() {
    log_debug_stream(_logger) << "Starting DynamoDB docker image" << std::endl;

    // Check docker image
    if (!_dockerService->ImageExists(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG)) {
      throw Core::ServiceException("Image does not exist", Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    // Check container image
    if (!_dockerService->ContainerExists(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG)) {
      throw Core::ServiceException("Container does not exist", Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    // Get docker container
    Dto::Docker::Container container = _dockerService->GetContainerByName(DYNAMODB_DOCKER_IMAGE, DYNAMODB_DOCKER_TAG);

    // Stop docker container, in case it is running.
    if (container.state == "running") {
      _dockerService->StopContainer(container);
      log_info_stream(_logger) << "Docker containers for DynamoDB stopped" << std::endl;
    } else {
      log_warning_stream(_logger) << "Docker containers for DynamoDB not running" << std::endl;
    }

  }

} // namespace AwsMock::Worker
