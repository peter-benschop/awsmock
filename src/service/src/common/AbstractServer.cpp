//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/AbstractServer.h>

#include <utility>

namespace AwsMock::Service {

  AbstractServer::AbstractServer(const Core::Configuration &configuration, std::string name) : _logger(Poco::Logger::get("AbstractServer")), _configuration(configuration), _name(std::move(name)), _running(false) {

    // Create environment
    _serviceDatabase = std::make_unique<Database::ModuleDatabase>(_configuration);
    log_debug_stream(_logger) << "AbstractServer initialized" << std::endl;
  }

  bool AbstractServer::IsActive(const std::string &name) {
    return _serviceDatabase->IsActive(_name);
  }

  bool AbstractServer::IsRunning() const {
    return _running;
  }

  void AbstractServer::run() {
    MainLoop();
    StopHttpServer();
    _serviceDatabase->SetStatus(_name, Database::Entity::Module::ModuleStatus::STOPPED);
    _running = false;
    log_info_stream(_logger) << "Module " << _name << " has been shutdown" << std::endl;
  }

  bool AbstractServer::InterruptableSleep(int period) {
    _mutex.lock();
    if (_condition.tryWait(_mutex, period)) {
      return true;
    }
    _mutex.unlock();
    return false;
  }

  void AbstractServer::StopServer() {
    _condition.signal();
  }

  void AbstractServer::StartHttpServer(int maxQueueLength, int maxThreads, const std::string &host, int port, Poco::Net::HTTPRequestHandlerFactory *requestFactory) {

    // Set HTTP server parameter
    auto *httpServerParams = new Poco::Net::HTTPServerParams();
    httpServerParams->setMaxQueued(maxQueueLength);
    httpServerParams->setMaxThreads(maxThreads);
    log_debug_stream(_logger) << "HTTP server parameter set, maxQueue: " << maxQueueLength << " maxThreads: " << maxThreads << std::endl;

    _serviceDatabase->SetPort(_name, port);
    _httpServer = std::make_shared<Poco::Net::HTTPServer>(requestFactory, Poco::Net::ServerSocket(Poco::UInt16(port)), httpServerParams);
    _httpServer->start();

    // Set running, now that the HTTP server is running
    _running = true;

    log_info_stream(_logger) << "HTTP server " << _name << " started, endpoint: http://" << host << ":" << port << std::endl;
  }

  void AbstractServer::StopHttpServer() {
    if (_httpServer) {
      _httpServer->stop();
      _httpServer.reset();
    }
  }

} // namespace AwsMock::Worker
