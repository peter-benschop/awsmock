//
// Created by vogje01 on 04/01/2023.
//

#include <utility>

#include "awsmock/controller/RestService.h"

namespace AwsMock {

  RestService::RestService(Core::Configuration &configuration) : _port(MANAGER_DEFAULT_PORT), _host(MANAGER_DEFAULT_HOST), _logger(Poco::Logger::get("RestService")), _configuration(configuration) {

    _port = _configuration.getInt("awsmock.manager.port", MANAGER_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.manager.host", MANAGER_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.manager.max.queue", MANAGER_MAX_CONNECTIONS);
    _maxThreads = _configuration.getInt("awsmock.manager.max.threads", MANAGER_MAX_THREADS);
    log_debug_stream(_logger) << "AwsMock manager initialized, endpoint: " << _host << ":" << _port << std::endl;
  }

  RestService::~RestService() {
    StopServer();
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

  void RestService::StartServer() {

    // Configure manager
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

  void RestService::StartServer(std::shared_ptr<Poco::Net::HTTPRequestHandlerFactory> router, int port) {
    setPort(port);
    setRouter(std::move(router));
    StartServer();
  }

  void RestService::StopServer() {
    //_router.reset();
    if (_httpServer) {
      _httpServer->stopAll(true);
      _httpServer.reset();
    }
  }
}
