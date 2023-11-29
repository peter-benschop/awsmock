//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/AbstractServer.h>

namespace AwsMock::Service {

  AbstractServer::AbstractServer(Core::Configuration &configuration, std::string name) : _logger(Poco::Logger::get("AbstractServer")), _configuration(configuration), _name(std::move(name)), _running(false) {

    // Create environment
    _moduleDatabase = std::make_unique<Database::ModuleDatabase>(_configuration);
    log_debug_stream(_logger) << "AbstractServer initialized" << std::endl;
  }

  bool AbstractServer::IsActive(const std::string &name) {
    return _moduleDatabase->IsActive(_name);
  }

  bool AbstractServer::IsRunning() const {
    return _running;
  }

  void AbstractServer::run() {
    MainLoop();
    StopHttpServer();
    _moduleDatabase->SetState(_name, Database::Entity::Module::ModuleState::STOPPED);
    _running = false;
    std::cerr << "Module: " << _name << " shutdown" << std::endl;
    log_info_stream(_logger) << "Module " << _name << " has been shutdown" << std::endl;
  }

  bool AbstractServer::InterruptableSleep(int period) {
    _mutex.lock();
    if (_condition.tryWait(_mutex, period)) {
      _mutex.unlock();
      return true;
    }
    _mutex.unlock();
    return false;
  }

  void AbstractServer::StopServer() {
    _condition.broadcast();
  }

  void AbstractServer::StartHttpServer(int maxQueueLength, int maxThreads, int requestTimeout, const std::string &host, int port, Poco::Net::HTTPRequestHandlerFactory *requestFactory) {

    // Set HTTP server parameter
    auto *httpServerParams = new Poco::Net::HTTPServerParams();
    httpServerParams->setMaxQueued(maxQueueLength);
    httpServerParams->setMaxThreads(maxThreads);
    httpServerParams->setTimeout(Poco::Timespan(requestTimeout, 0));
    httpServerParams->setKeepAlive(true);
    log_debug_stream(_logger) << "HTTP server parameter set, maxQueue: " << maxQueueLength << " maxThreads: " << maxThreads << std::endl;

    _moduleDatabase->SetPort(_name, port);
    _httpServer = std::make_shared<Poco::Net::HTTPServer>(requestFactory, Poco::Net::ServerSocket(Poco::UInt16(port)), httpServerParams);
    _httpServer->start();

    // Set running, now that the HTTP server is running
    _running = true;
    _moduleDatabase->SetState(_name, Database::Entity::Module::ModuleState::RUNNING);

    log_info_stream(_logger) << "HTTP server " << _name << " started, endpoint: http://" << host << ":" << port << std::endl;
  }

  void AbstractServer::StopHttpServer() {
    if (_httpServer) {
      _httpServer->stop();
      _httpServer.reset();
    }
  }

} // namespace AwsMock::Worker
