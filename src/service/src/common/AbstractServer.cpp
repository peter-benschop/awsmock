//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/common/AbstractServer.h>

namespace AwsMock::Service {

  AbstractServer::AbstractServer(Core::Configuration &configuration, std::string name, int timeout) : Timer(name, timeout), _configuration(configuration), _moduleDatabase(Database::ModuleDatabase::instance()), _name(std::move(name)), _running(false) {

    // Create environment
    log_debug << "AbstractServer initialized, name: " << _name;
  }

  bool AbstractServer::IsActive(const std::string &name) {
    return _moduleDatabase.IsActive(name);
  }

  bool AbstractServer::IsRunning() const {
    return _running;
  }

  void AbstractServer::StopServer() {
    _condition.broadcast();
    log_debug << "Stop broadcast";
  }

  void AbstractServer::StartHttpServer(int maxQueueLength, int maxThreads, int requestTimeout, const std::string &host, int port, Poco::Net::HTTPRequestHandlerFactory *requestFactory) {

    // Set HTTP server parameter
    auto *httpServerParams = new Poco::Net::HTTPServerParams();
    httpServerParams->setMaxQueued(maxQueueLength);
    httpServerParams->setMaxThreads(maxThreads);
    httpServerParams->setTimeout(Poco::Timespan(requestTimeout, 0));
    httpServerParams->setKeepAlive(true);
    log_debug << "HTTP server parameter set, name: " << _name << " maxQueue: " << maxQueueLength << " maxThreads: " << maxThreads;

    _moduleDatabase.SetPort(_name, port);
    _httpServer = std::make_shared<Poco::Net::HTTPServer>(requestFactory, Poco::Net::ServerSocket(Poco::UInt16(port)), httpServerParams);
    _httpServer->start();

    // Set running, now that the HTTP server is running
    _running = true;
    _moduleDatabase.SetState(_name, Database::Entity::Module::ModuleState::RUNNING);

    log_info << "HTTP server " << _name << " started, endpoint: http://" << host << ":" << port;
  }

  void AbstractServer::StopHttpServer() {
    if (_httpServer) {
      _httpServer->stopAll(true);
      log_debug << "HTTP server stopped: " << _name;
    }
  }

  AbstractServer::~AbstractServer() {
    Stop();
  }

} // namespace AwsMock::Worker
