//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/lambda/LambdaServer.h"

namespace AwsMock::Service {

  LambdaServer::LambdaServer(Core::Configuration &configuration, Core::MetricService &metricService)
    : AbstractWorker(configuration), AbstractServer(configuration, "lambda"), _configuration(configuration), _metricService(metricService), _lambdaDatabase(Database::LambdaDatabase::instance()), _module("lambda") {

    // Get HTTP configuration values
    _port = _configuration.getInt("awsmock.service.lambda.port", LAMBDA_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.lambda.host", LAMBDA_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.lambda.max.queue", LAMBDA_DEFAULT_QUEUE);
    _maxThreads = _configuration.getInt("awsmock.service.lambda.max.threads", LAMBDA_DEFAULT_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.lambda.timeout", LAMBDA_DEFAULT_TIMEOUT);

    // Directories
    _dataDir = _configuration.getString("awsmock.data.dir") + Poco::Path::separator() + "lambda";
    log_debug << "lambda directory: " << _dataDir;

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.lambda.period", 10000);
    log_debug << "lambda manager period: " << _period;

    // Create environment
    _region = _configuration.getString("awsmock.region");

    // lambda module connection
    _lambdaServiceHost = _configuration.getString("awsmock.service.lambda.host", "localhost");
    _lambdaServicePort = _configuration.getInt("awsmock.service.lambda.port", 9503);
    log_debug << "lambda module endpoint: http://" << _lambdaServiceHost << ":" << _lambdaServicePort;

    // Docker module
    _dockerService = std::make_unique<Service::DockerService>(_configuration);

    // Create lambda directory
    Core::DirUtils::EnsureDirectory(_dataDir);
    log_debug << "LambdaWorker initialized";
  }

  LambdaServer::~LambdaServer() {
    StopServer();
  }

  void LambdaServer::Initialize() {


    // Check module active
    if (!IsActive("lambda")) {
      log_info << "Lambda module inactive";
      return;
    }
    log_info << "Lambda server starting";

    // Start HTTP manager
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new LambdaRequestHandlerFactory(_configuration, _metricService));

    // Cleanup
    CleanupContainers();

    // Start all lambda functions
    StartLambdaFunctions();
  }

  void LambdaServer::Run() {
    log_trace << "S3 processing started";
    UpdateCounters();
  }

  void LambdaServer::Shutdown() {
    StopHttpServer();
  }

  void LambdaServer::CleanupContainers() {
    _dockerService->PruneContainers();
    log_debug << "Docker containers cleaned up";
  }

  void LambdaServer::StartLambdaFunctions() {

    log_debug << "Starting lambdas";
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
      log_debug << "lambda started, name:" << lambda.function;
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
      log_debug << "Loaded lambda from file:" << lambda.fileName << " size: " << Core::FileUtils::FileSize(lambda.fileName);
    }
    return code;
  }

  void LambdaServer::SendCreateFunctionRequest(Dto::Lambda::CreateFunctionRequest &lambdaRequest, const std::string &contentType) {

    std::string url = "http://" + _lambdaServiceHost + ":" + std::to_string(_lambdaServicePort) + "/2015-03-31/functions";
    std::string body = lambdaRequest.ToJson();
    SendPostRequest(_module, url, body, contentType);
    log_debug << "lambda create function request send";
  }

  void LambdaServer::UpdateCounters() {
    long lambdas = _lambdaDatabase.LambdaCount();
    _metricService.SetGauge("lambda_count_total", lambdas);
  }

} // namespace AwsMock::Worker
