//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/LambdaServer.h>

namespace AwsMock::Service {

  LambdaServer::LambdaServer(Core::Configuration &configuration, Core::MetricService &metricService, Poco::NotificationQueue &createQueue, Poco::NotificationQueue &invokeQueue)
      : AbstractWorker(configuration), AbstractServer(configuration, "lambda"), _logger(Poco::Logger::get("LambdaServer")), _configuration(configuration), _metricService(metricService), _lambdaDatabase(Database::LambdaDatabase::instance()),
        _createQueue(createQueue), _invokeQueue(invokeQueue), _module("lambda") {

    // Get HTTP configuration values
    _port = _configuration.getInt("awsmock.service.lambda.port", LAMBDA_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.lambda.host", LAMBDA_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.lambda.max.queue", LAMBDA_DEFAULT_QUEUE);
    _maxThreads = _configuration.getInt("awsmock.service.lambda.max.threads", LAMBDA_DEFAULT_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.lambda.timeout", LAMBDA_DEFAULT_TIMEOUT);

    // Directories
    _dataDir = _configuration.getString("awsmock.data.dir") + Poco::Path::separator() + "lambda";
    _logger.debug() << "lambda directory: " << _dataDir << std::endl;

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.lambda.period", 10000);
    log_debug_stream(_logger) << "lambda manager period: " << _period << std::endl;

    // Create environment
    _region = _configuration.getString("awsmock.region");

    // lambda module connection
    _lambdaServiceHost = _configuration.getString("awsmock.service.lambda.host", "localhost");
    _lambdaServicePort = _configuration.getInt("awsmock.service.lambda.port", 9503);
    log_debug_stream(_logger) << "lambda module endpoint: http://" << _lambdaServiceHost << ":" << _lambdaServicePort << std::endl;

    // Docker module
    _dockerService = std::make_unique<Service::DockerService>(_configuration);

    // Create lambda directory
    Core::DirUtils::EnsureDirectory(_dataDir);
    log_debug_stream(_logger) << "LambdaWorker initialized" << std::endl;
  }

  LambdaServer::~LambdaServer() {
    StopServer();
  }

  void LambdaServer::MainLoop() {

    // Check module active
    if (!IsActive("lambda")) {
      log_info_stream(_logger) << "lambda module inactive" << std::endl;
      return;
    }
    log_info_stream(_logger) << "lambda worker started" << std::endl;

    // Start creator/executor
    Poco::ThreadPool::defaultPool().start(_lambdaCreator);
    Poco::ThreadPool::defaultPool().start(_lambdaExecutor);

    // Start monitoring thread
    StartMonitoringServer();

    // Start HTTP manager
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new LambdaRequestHandlerFactory(_configuration, _metricService, _createQueue, _invokeQueue));

    // Cleanup
    CleanupContainers();

    // Start all lambda functions
    StartLambdaFunctions();

    while (IsRunning()) {

      log_debug_stream(_logger) << "LambdaWorker processing started" << std::endl;

      // Wait for timeout or condition
      if (InterruptableSleep(_period)) {
        StopMonitoringServer();
        StopExecutors();
        break;
      }
    }
  }

  void LambdaServer::StartMonitoringServer() {
    _threadPool.StartThread(_configuration, _metricService, _condition);
  }

  void LambdaServer::StopMonitoringServer() {
    _threadPool.stopAll();
  }

  void LambdaServer::StopExecutors() {
    _createQueue.wakeUpAll();
    _invokeQueue.wakeUpAll();
    Poco::ThreadPool::defaultPool().joinAll();
  }

  void LambdaServer::CleanupContainers() {
    _dockerService->PruneContainers();
    log_debug_stream(_logger) << "Docker containers cleaned up" << std::endl;
  }

  void LambdaServer::StartLambdaFunctions() {

    log_debug_stream(_logger) << "Starting lambdas" << std::endl;
    std::vector<Database::Entity::Lambda::Lambda> lambdas = _lambdaDatabase.ListLambdas(_region);

    for (auto &lambda : lambdas) {

      Dto::Lambda::Code code = GetCode(lambda);

      // Create create function request
      Dto::Lambda::CreateFunctionRequest request = {
          .region=lambda.region,
          .functionName=lambda.function,
          .runtime=lambda.runtime,
          .code=code,
          .tags=lambda.tags
      };
      SendCreateFunctionRequest(request, "application/json");
      log_debug_stream(_logger) << "lambda started, name:" << lambda.function << std::endl;
    }
  }

  Dto::Lambda::Code LambdaServer::GetCode(const Database::Entity::Lambda::Lambda &lambda) {

    Dto::Lambda::Code code;
    if (Core::FileUtils::FileExists(lambda.fileName)) {
      std::stringstream ss;
      std::ifstream ifs(lambda.fileName);
      ss << ifs.rdbuf();
      ifs.close();

      code = {
          .zipFile=ss.str()
      };
      log_debug_stream(_logger) << "Loaded lambda from file:" << lambda.fileName << " size: " << Core::FileUtils::FileSize(lambda.fileName) << std::endl;
    }
    return code;
  }

  void LambdaServer::SendCreateFunctionRequest(Dto::Lambda::CreateFunctionRequest &lambdaRequest, const std::string &contentType) {

    std::string url = "http://" + _lambdaServiceHost + ":" + std::to_string(_lambdaServicePort) + "/2015-03-31/functions";
    std::string body = lambdaRequest.ToJson();
    SendPostRequest(_module, url, body, contentType);
    log_debug_stream(_logger) << "lambda create function request send" << std::endl;
  }

} // namespace AwsMock::Worker
