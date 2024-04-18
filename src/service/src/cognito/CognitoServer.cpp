//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/service/cognito/CognitoServer.h"

namespace AwsMock::Service {

  CognitoServer::CognitoServer(Core::Configuration &configuration, Core::MetricService &metricService)
    : AbstractWorker(configuration), AbstractServer(configuration, "cognito"), _configuration(configuration), _metricService(metricService), _module("cognito"), _running(false), _moduleDatabase(Database::ModuleDatabase::instance()),
      _cognitoDatabase(Database::CognitoDatabase::instance()) {

    // Get HTTP configuration values
    _port = _configuration.getInt("awsmock.service.cognito.port", COGNITO_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.cognito.host", COGNITO_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.cognito.max.queue", COGNITO_DEFAULT_QUEUE_SIZE);
    _maxThreads = _configuration.getInt("awsmock.service.cognito.max.threads", COGNITO_DEFAULT_MAX_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.cognito.timeout", COGNITO_DEFAULT_TIMEOUT);

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.cognito.period", 10000);
    log_debug << "Worker period: " << _period;

    // Create environment
    _region = _configuration.getString("awsmock.region", "eu-central_1");
    _accountId = _configuration.getString("awsmock.account.userPoolId", "000000000000");
    _clientId = _configuration.getString("awsmock.client.userPoolId", "00000000");
    _user = _configuration.getString("awsmock.user", "none");
    log_debug << "Cognito module initialized, endpoint: " << _host << ":" << _port;
  }

  void CognitoServer::Initialize() {

    // Check module active
    if (!IsActive("cognito")) {
      log_info << "Cognito module inactive";
      return;
    }
    log_info << "Cognito module starting";

    // Start REST module
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new CognitoHandlerFactory(_configuration, _metricService));
  }

  void CognitoServer::Run() {
    log_trace << "Cognito processing started";
      UpdateCounters();
  }

  void CognitoServer::Shutdown() {
    StopHttpServer();
  }

  void CognitoServer::UpdateCounters() {
    long userPools = _cognitoDatabase.CountUserPools();
    _metricService.SetGauge("cognito_userpool_count_total", userPools);
  }

}
