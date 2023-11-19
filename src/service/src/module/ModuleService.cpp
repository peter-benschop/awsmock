//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/service/ModuleService.h>

namespace AwsMock::Service {

  ModuleService::ModuleService(Core::Configuration &configuration, Service::ServerMap &serverMap) : _logger(Poco::Logger::get("ModuleService")), _configuration(configuration), _serverMap(serverMap) {

    _moduleDatabase = std::make_shared<Database::ModuleDatabase>(_configuration);
  }

  Database::Entity::Module::ModuleList ModuleService::ListModules() {

    Database::Entity::Module::ModuleList modules = _moduleDatabase->ListModules();
    log_debug_stream(_logger) << "Module list, count: " << modules.size() << std::endl;
    return modules;
  }

  bool ModuleService::IsRunning(const std::string &moduleName) {

    Database::Entity::Module::Module module = _moduleDatabase->GetModuleByName(moduleName);
    log_debug_stream(_logger) << "Module state, state: " << Database::Entity::Module::ModuleStateToString(module.state) << std::endl;
    return module.state == Database::Entity::Module::ModuleState::RUNNING;
  }

  Database::Entity::Module::Module ModuleService::StartService(const std::string &name) {

    // Set state
    Database::Entity::Module::Module module = _moduleDatabase->GetModuleByName(name);
    if (module.state == Database::Entity::Module::ModuleState::RUNNING) {

      log_info_stream(_logger) << "Module " + name + " already running" << std::endl;
      throw Core::ServiceException("Module " + name + " already running", Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

    } else {

      // Set state
      _moduleDatabase->SetState(name, Database::Entity::Module::ModuleState::RUNNING);

      if (module.name == "database") {
        _moduleDatabase->StartDatabase();
      } else if (module.name == "s3") {
        auto *s3server = (Service::S3Server *) _serverMap[module.name];
        Poco::ThreadPool::defaultPool().start(*s3server);
      } else if (module.name == "sqs") {
        auto *sqsServer = (Service::SQSServer *) _serverMap[module.name];
        Poco::ThreadPool::defaultPool().start(*sqsServer);
      } else if (module.name == "sns") {
        auto *snsServer = (Service::SNSServer *) _serverMap[module.name];
        Poco::ThreadPool::defaultPool().start(*snsServer);
      } else if (module.name == "lambda") {
        auto *lambdaServer = (Service::LambdaServer *) _serverMap[module.name];
        Poco::ThreadPool::defaultPool().start(*lambdaServer);
      } else if (module.name == "transfer") {
        auto *transferServer = (Service::TransferServer *) _serverMap[module.name];
        Poco::ThreadPool::defaultPool().start(*transferServer);
      } else if (module.name == "gateway") {
        auto *gatewayServer = (Service::GatewayServer *) _serverMap[module.name];
        Poco::ThreadPool::defaultPool().start(*gatewayServer);
      }
      log_info_stream(_logger) << "Module " + name + " started" << std::endl;
    }
    return module;
  }

  void ModuleService::StartAllServices() {

    Database::Entity::Module::ModuleList modules = _moduleDatabase->ListModules();
    for (const auto &module : modules) {
      StartService(module.name);
    }
  }

  Database::Entity::Module::Module ModuleService::RestartService(const std::string &name) {

    // Set state
    Database::Entity::Module::Module module = _moduleDatabase->GetModuleByName(name);
    if (module.state == Database::Entity::Module::ModuleState::RUNNING) {

      StopService(name);
      log_info_stream(_logger) << "Module " + name + " already running" << std::endl;
      throw Core::ServiceException("Module " + name + " already running", Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

    }

    log_info_stream(_logger) << "Module " + name + " restarted" << std::endl;
    return StartService(name);
  }

  void ModuleService::RestartAllServices() {

    Database::Entity::Module::ModuleList modules = _moduleDatabase->ListModules();
    for (const auto &module : modules) {
      RestartService(module.name);
    }
  }

  Database::Entity::Module::Module ModuleService::StopService(const std::string &name) {

    // Set state
    Database::Entity::Module::Module module = _moduleDatabase->GetModuleByName(name);
    if (module.state != Database::Entity::Module::ModuleState::RUNNING) {

      throw Core::ServiceException("Module " + name + " not running", Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

    } else {

      // Set state
      _moduleDatabase->SetState(name, Database::Entity::Module::ModuleState::STOPPED);

      // Stop module
      if (name == "database") {
        _moduleDatabase->StopDatabase();
      } else {
        for (const auto &server : _serverMap) {
          if (name == server.first) {
            server.second->StopServer();
            log_info_stream(_logger) << "Module " << name << " stopped" << std::endl;
          }
        }
      }
    }
    return module;
  }

  void ModuleService::StopAllServices() {

    Database::Entity::Module::ModuleList modules = _moduleDatabase->ListModules();
    for (const auto &module : modules) {
      StopService(module.name);
    }
  }
}