//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/secretsmanager/SecretsManagerServer.h>

namespace AwsMock::Service {

  SecretsManagerServer::SecretsManagerServer(Core::Configuration &configuration, Core::MetricService &metricService)
    : AbstractServer(configuration, "secretsmanager"), _logger(Poco::Logger::get("SecretsManagerServer")), _configuration(configuration), _metricService(metricService), _moduleDatabase(Database::ModuleDatabase::instance()) {

    // HTTP manager configuration
    _port = _configuration.getInt("awsmock.service.secretsmanager.port", SECRETSMANAGER_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.secretsmanager.host", SECRETSMANAGER_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.secretsmanager.max.queue", SECRETSMANAGER_DEFAULT_QUEUE_LENGTH);
    _maxThreads = _configuration.getInt("awsmock.service.secretsmanager.max.threads", SECRETSMANAGER_DEFAULT_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.secretsmanager.timeout", SECRETSMANAGER_DEFAULT_TIMEOUT);
    log_debug_stream(_logger) << "SecretsManager rest module initialized, endpoint: " << _host << ":" << _port << std::endl;

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.secretsmanager.period", 10000);

    // Create environment
    _region = _configuration.getString("awsmock.region");
    log_debug_stream(_logger) << "SecretsManager server initialized" << std::endl;
  }

  SecretsManagerServer::~SecretsManagerServer() {
    StopServer();
  }

  void SecretsManagerServer::MainLoop() {

    // Check module active
    if (!IsActive("secretsmanager")) {
      log_info_stream(_logger) << "SecretsManager module inactive" << std::endl;
      return;
    }
    log_info_stream(_logger) << "SecretsManager server starting, port: " << _port << std::endl;

    // Start monitoring thread
    StartMonitoringServer();

    // Start REST module
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new SecretsManagerRequestHandlerFactory(_configuration, _metricService, _condition));

    while (IsRunning()) {

      log_debug_stream(_logger) << "SecretsManager processing started" << std::endl;

      // Wait for timeout or condition
      if (InterruptableSleep(_period)) {
        StopMonitoringServer();
        break;
      }
    }
  }

  void SecretsManagerServer::StartMonitoringServer() {
    _threadPool.StartThread(_configuration, _metricService, _condition);
  }

  void SecretsManagerServer::StopMonitoringServer() {
    _threadPool.stopAll();
  }

} // namespace AwsMock::Worker
