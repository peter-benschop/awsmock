//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/gateway/GatewayServer.h"

namespace AwsMock::Service {

  GatewayServer::GatewayServer(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractServer(configuration, "gateway", 10), _configuration(configuration), _metricService(metricService), _running(false){

    // Get HTTP configuration values
    _port = _configuration.getInt("awsmock.service.gateway.port", GATEWAY_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.gateway.host", GATEWAY_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.gateway.max.queue", GATEWAY_MAX_QUEUE);
    _maxThreads = _configuration.getInt("awsmock.service.gateway.max.threads", GATEWAY_MAX_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.gateway.timeout", GATEWAY_TIMEOUT);

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.lambda.period", 10000);
    log_debug << "Gateway worker period: " << _period;

    // Create environment
    _region = _configuration.getString("awsmock.region");
    log_debug << "GatewayServer initialized";
  }

  GatewayServer::~GatewayServer() {
    StopServer();
  }

  void GatewayServer::Initialize() {

    // Check module active
    if (!IsActive("gateway")) {
      log_info << "Gateway module inactive";
      return;
    }
    log_info << "Gateway server starting";

    // Start HTTP manager
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new GatewayRouter(_configuration, _metricService));
  }

  void GatewayServer::Run() {
  }

  void GatewayServer::Shutdown() {
    StopHttpServer();
  }

} // namespace AwsMock::Service
