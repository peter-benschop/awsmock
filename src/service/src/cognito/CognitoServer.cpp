//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/CognitoServer.h>

namespace AwsMock::Service {

  CognitoServer::CognitoServer(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractWorker(configuration), AbstractServer(configuration, "cognito"), _logger(Poco::Logger::get("CognitoServer")), _configuration(configuration), _metricService(metricService), _module("cognito") {

    // Get HTTP configuration values
    _port = _configuration.getInt("awsmock.service.cognito.port", COGNITO_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.cognito.host", COGNITO_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.cognito.max.queue", COGNITO_DEFAULT_QUEUE_SIZE);
    _maxThreads = _configuration.getInt("awsmock.service.cognito.max.threads", COGNITO_DEFAULT_MAX_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.cognito.timeout", COGNITO_DEFAULT_TIMEOUT);

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.cognito.period", 10000);
    log_debug_stream(_logger) << "Worker period: " << _period << std::endl;

    // Create environment
    _region = _configuration.getString("awsmock.region", "eu-central_1");
    _accountId = _configuration.getString("awsmock.account.id", "000000000000");
    _clientId = _configuration.getString("awsmock.client.id", "00000000");
    _user = _configuration.getString("awsmock.user", "none");

    // Database connections
    _moduleDatabase = std::make_unique<Database::ModuleDatabase>(_configuration);
    _cognitoDatabase = std::make_unique<Database::CognitoDatabase>(_configuration);
    log_debug_stream(_logger) << "Cognito module initialized, endpoint: " << _host << ":" << _port << std::endl;
  }

  CognitoServer::~CognitoServer() {
    StopServer();
  }

  void CognitoServer::MainLoop() {

    // Check module active
    if (!IsActive("s3")) {
      log_info_stream(_logger) << "Cognito module inactive" << std::endl;
      return;
    }
    log_info_stream(_logger) << "Cognito module starting" << std::endl;

    // Start monitoring thread
    StartMonitoringServer();

    // Start REST module
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new CognitoHandlerFactory(_configuration, _metricService));

    while (IsRunning()) {

      log_debug_stream(_logger) << "Cognito processing started" << std::endl;

      // Wait for timeout or condition
      if (InterruptableSleep(_period)) {
        StopMonitoringServer();
        break;
      }
      UpdateCounters();
    }
  }

  void CognitoServer::StartMonitoringServer() {
    _threadPool.StartThread(_configuration, _metricService, _condition);
  }

  void CognitoServer::StopMonitoringServer() {
    _threadPool.stopAll();
  }

  void CognitoServer::UpdateCounters() {
    /*long buckets = _cognitoDatabase->BucketCount();
    long objects = _cognitoDatabase->ObjectCount();
    _metricService.SetGauge("s3_bucket_count", buckets);
    _metricService.SetGauge("s3_object_count", objects);*/
  }
}
