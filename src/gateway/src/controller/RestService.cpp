//
// Created by vogje01 on 04/01/2023.
//

#include <utility>

#include "awsmock/controller/RestService.h"

namespace AwsMock {

  RestService::RestService(Core::Configuration &configuration)
      : _port(GATEWAY_DEFAULT_PORT), _host(GATEWAY_DEFAULT_HOST), _logger(Poco::Logger::get("RestService")), _configuration(configuration) {

    _port = _configuration.getInt("awsmock.gateway.port", GATEWAY_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.gateway.host", GATEWAY_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.gateway.max.queue", GATEWAY_MAX_CONNECTIONS);
    _maxThreads = _configuration.getInt("awsmock.gateway.max.threads", GATEWAY_MAX_THREADS);
    log_debug_stream(_logger) << "Rest service initialized, endpoint: " << _host << ":" << _port << std::endl;
  }

  RestService::~RestService() {

    _router.reset();
    if (_httpServer) {
      _httpServer->stopAll(true);
      _httpServer.reset();
    }
  }

  void RestService::setPort(int port) {
    _port = port;
  }

  void RestService::setRouter(std::shared_ptr<Poco::Net::HTTPRequestHandlerFactory> router) {
    _router = std::move(router);
  }

  std::shared_ptr<Poco::Net::HTTPRequestHandlerFactory> RestService::getRouter() {
    return _router;
  }

  void RestService::start() {

    // Configure server
    auto *httpServerParams = new Poco::Net::HTTPServerParams();

    httpServerParams->setMaxQueued(_maxQueueLength);
    httpServerParams->setMaxThreads(_maxThreads);
    Poco::ThreadPool::defaultPool().addCapacity(_maxQueueLength - Poco::ThreadPool::defaultPool().available());

    _httpServer = std::make_shared<Poco::Net::HTTPServer>(_router.get(), Poco::Net::ServerSocket(Poco::UInt16(_port)), httpServerParams);

    if (_httpServer) {
      _httpServer->start();
      log_info_stream(_logger) << "AwsMock gateway started, endpoint: http://" << _host << ":" << _port << std::endl;
    }
  }

  void RestService::start(std::shared_ptr<Poco::Net::HTTPRequestHandlerFactory> router, int port) {
    setPort(port);
    setRouter(std::move(router));
    start();
  }
}
