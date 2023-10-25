//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/GatewayServer.h>

namespace AwsMock::Service {

  GatewayServer::GatewayServer(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractServer(configuration, "gateway"), _logger(Poco::Logger::get("GatewayServer")), _configuration(configuration), _metricService(metricService),_running(false) {

    // Get HTTP configuration values
    _port = _configuration.getInt("awsmock.service.gateway.port", GATEWAY_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.gateway.host", GATEWAY_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.gateway.max.queue", GATEWAY_MAX_QUEUE);
    _maxThreads = _configuration.getInt("awsmock.service.gateway.max.threads", GATEWAY_MAX_THREADS);

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.lambda.period", 10000);
    log_debug_stream(_logger) << "Gateway worker period: " << _period << std::endl;

    // Create environment
    _region = _configuration.getString("awsmock.region");
    log_debug_stream(_logger) << "GatewayServer initialized" << std::endl;
  }

  GatewayServer::~GatewayServer() {
    StopServer();
  }

  void GatewayServer::MainLoop() {

    // Check service active
    if (!IsActive("gateway")) {
      log_info_stream(_logger) << "Gateway service inactive" << std::endl;
      return;
    }
    log_info_stream(_logger) << "Gateway server starting" << std::endl;

    // Start monitoring thread
    StartMonitoringServer();

    // Start HTTP manager
    StartHttpServer(_maxQueueLength, _maxThreads, _host, _port, new GatewayRouter(_configuration, _metricService));

    _running = true;
    while (_running) {

      log_debug_stream(_logger) << "Gateway processing started" << std::endl;

      // Wait for timeout or condition
      if (InterruptableSleep(_period)) {
        break;
      }
    }
  }

  void GatewayServer::StartMonitoringServer() {
    //_threadPool.StartThread(_configuration, _metricService, _condition);
  }

  void GatewayServer::StopMonitoringServer() {
    //_threadPool.stopAll();
  }

} // namespace AwsMock::Service
