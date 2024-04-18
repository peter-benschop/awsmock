//
// Created by vogje01 on 04/01/2023.
//

#include <utility>

#include "awsmock/controller/RestService.h"

namespace AwsMock {

  RestService::RestService(Core::Configuration &configuration) : _port(MANAGER_DEFAULT_PORT), _host(MANAGER_DEFAULT_HOST), _configuration(configuration) {

    _port = _configuration.getInt("awsmock.manager.port", MANAGER_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.manager.host", MANAGER_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.manager.max.queue", MANAGER_MAX_CONNECTIONS);
    _maxThreads = _configuration.getInt("awsmock.manager.max.threads", MANAGER_MAX_THREADS);

    log_debug << "AwsMock manager initialized, endpoint: " << _host << ":" << _port;
  }

  void RestService::setPort(int port) {
    _port = port;
  }

  void RestService::setRouter(Poco::Net::HTTPRequestHandlerFactory* router) {
    _router = router;
  }

  void RestService::StartServer() {

    // Configure manager
    auto *httpServerParams = new Poco::Net::HTTPServerParams();

    httpServerParams->setMaxQueued(_maxQueueLength);
    httpServerParams->setMaxThreads(_maxThreads);
    _httpServer = std::make_shared<Poco::Net::HTTPServer>(_router, Poco::Net::ServerSocket(Poco::UInt16(_port)), httpServerParams);

    if (_httpServer) {
      _httpServer->start();
      log_info << "AwsMock manager started, endpoint: http://" << _host << ":" << _port;
    }
  }

  void RestService::StartServer(Poco::Net::HTTPRequestHandlerFactory* router, int port) {
    setPort(port);
    setRouter(router);
    StartServer();
  }

  void RestService::StopServer() {
    if (_httpServer) {
      _httpServer->stop();
    }
  }
}
