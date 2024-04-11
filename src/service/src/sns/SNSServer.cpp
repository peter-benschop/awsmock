//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/sns/SNSServer.h"

namespace AwsMock::Service {

  SNSServer::SNSServer(Core::Configuration &configuration, Core::MetricService &metricService)
    : AbstractServer(configuration, "sns"), _logger(Poco::Logger::get("SNSServer")), _configuration(configuration), _metricService(metricService), _snsDatabase(Database::SNSDatabase::instance()) {

    // HTTP manager configuration
    _port = _configuration.getInt("awsmock.service.sns.port", SNS_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.sns.host", SNS_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.sns.max.queue", SNS_DEFAULT_QUEUE_LENGTH);
    _maxThreads = _configuration.getInt("awsmock.service.sns.max.threads", SNS_DEFAULT_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.sns.timeout", SNS_DEFAULT_TIMEOUT);
    log_debug_stream(_logger) << "SNS rest module initialized, endpoint: " << _host << ":" << _port << std::endl;

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.sqs.period", 10000);

    // Create environment
    _region = _configuration.getString("awsmock.region");
    log_debug_stream(_logger) << "SNSServer initialized" << std::endl;
  }

  SNSServer::~SNSServer() {
    StopServer();
  }

  void SNSServer::MainLoop() {

    // Check module active
    if (!IsActive("sns")) {
      log_info_stream(_logger) << "SNS module inactive" << std::endl;
      return;
    }

    log_info_stream(_logger) << "SNS module starting" << std::endl;

    // Start monitoring thread
    StartMonitoringServer();

    // Start REST module
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new SNSRequestHandlerFactory(_configuration, _metricService, _condition));

    while (IsRunning()) {

      log_trace_stream(_logger) << "SNSServer processing started" << std::endl;

      // Wait for timeout or condition
      if (InterruptableSleep(_period)) {
        StopMonitoringServer();
        break;
      }
    }
  }

  void SNSServer::StartMonitoringServer() {
    _threadPool.StartThread(_configuration, _metricService, _condition);
  }

  void SNSServer::StopMonitoringServer() {
    _threadPool.stopAll();
  }

} // namespace AwsMock::Worker
