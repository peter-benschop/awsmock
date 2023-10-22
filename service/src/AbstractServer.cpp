//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/AbstractServer.h>

namespace AwsMock::Service {

  AbstractServer::AbstractServer(const Core::Configuration &configuration, Poco::Condition &condition)
      : _condition(condition), _logger(Poco::Logger::get("AbstractServer")), _configuration(configuration), _running(false) {

    // Create environment
    _serviceDatabase = std::make_unique<Database::ServiceDatabase>(_configuration);
    log_debug_stream(_logger) << "AbstractServer initialized" << std::endl;
  }

  bool AbstractServer::IsActive(const std::string &name) {
    return _serviceDatabase->IsActive(name);
  }

  void AbstractServer::run() {
      MainLoop();
  }

  bool AbstractServer::InterruptableSleep(int period) {
    _mutex.lock();
    if (_condition.tryWait(_mutex, period)) {
      return true;
    }
    _mutex.unlock();
    return false;
  }
} // namespace AwsMock::Worker
