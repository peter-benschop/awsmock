
#include <awsmock/resource/handler/ModuleHandler.h>

namespace AwsMock {

  ModuleHandler::ModuleHandler(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractResource(), _logger(Poco::Logger::get("TransferHandler")), _configuration(configuration), _metricService(metricService) {

    _serviceDatabase = std::make_shared<Database::ModuleDatabase>(_configuration);
  }

  void ModuleHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_GET_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "GET");
    log_debug_stream(_logger) << "Module GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    Database::Entity::Module::ModuleList modules = _serviceDatabase->ListModules();
    std::string body = Dto::Module::Module::ToJson(modules);

    SendOkResponse(response, body);
  }

  void ModuleHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_PUT_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "PUT");
    log_debug_stream(_logger) << "Module PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {
      std::string name = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string action = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);
      log_info_stream(_logger) << "Module: " << name << " action: " << action << std::endl;

      if (action == "start") {

        // Set status
        Database::Entity::Module::Module module = _serviceDatabase->GetModuleByName(name);
        if (module.status == Database::Entity::Module::ModuleStatus::RUNNING) {

          throw Core::ServiceException("Module already running", Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

        } else {

          // Set status
          _serviceDatabase->SetStatus(name, Database::Entity::Module::ModuleStatus::RUNNING);

          Service::S3Server server = Service::S3Server(_configuration, _metricService);
          Poco::ThreadPool::defaultPool().start(server, name);

          // Send response
          std::string body = Dto::Module::Module::ToJson(module);
          SendOkResponse(response, body);
        }
      } else if (action == "stop") {

        // Set status
        Database::Entity::Module::Module module = _serviceDatabase->GetModuleByName(name);
        if (module.status != Database::Entity::Module::ModuleStatus::RUNNING) {

          throw Core::ServiceException("Module not running", Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);

        } else {

          // Set status
          _serviceDatabase->SetStatus(name, Database::Entity::Module::ModuleStatus::STOPPED);

          Service::S3Server server = Service::S3Server(_configuration, _metricService);
          Poco::ThreadPool::defaultPool().start(server, name);

          Poco::TaskManager tm;
          Poco::TaskManager::TaskList l = tm.taskList();

          // Send response
          std::string body = Dto::Module::Module::ToJson(module);
          SendOkResponse(response, body);
        }
      }

    } catch (Core::ServiceException &exc) {
      SendErrorResponse("Module", response, exc);
    }
  }

  void ModuleHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_POST_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "POST");
    log_debug_stream(_logger) << "Module POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    SendOkResponse(response);
  }

  void ModuleHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_DELETE_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "DELETE");
    log_debug_stream(_logger) << "Module DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;
    SendOkResponse(response);
  }

  void ModuleHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_HEAD_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "HEAD");
    log_debug_stream(_logger) << "Module HEAD request, address: " << request.clientAddress().toString() << std::endl;
    SendOkResponse(response);
  }

  void ModuleHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_OPTIONS_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "OPTIONS");
    log_debug_stream(_logger) << "Module OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
