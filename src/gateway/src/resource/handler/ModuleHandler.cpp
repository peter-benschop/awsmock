
#include <awsmock/resource/handler/ModuleHandler.h>

namespace AwsMock {

  ModuleHandler::ModuleHandler(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractResource(), _logger(Poco::Logger::get("TransferHandler")), _configuration(configuration), _metricService(metricService) {

      _serviceDatabase = std::make_shared<Database::ServiceDatabase>(_configuration);
  }

  void ModuleHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_GET_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "GET");
    log_debug_stream(_logger) << "Transfer GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    Database::Entity::Service::ServiceList serviceList = _serviceDatabase->ListServices();
    std::string body = ToJson(serviceList);

    SendOkResponse(response, body);
  }

  void ModuleHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_PUT_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "PUT");
    log_debug_stream(_logger) << "Transfer PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    //SetHeaders(request, region, user);
    //ForwardRequest(request, response, _transferServiceHost, _transferServicePort);
  }

  void ModuleHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_POST_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "POST");
    log_debug_stream(_logger) << "Transfer POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    //SetHeaders(request, region, user);
    //ForwardRequest(request, response, _transferServiceHost, _transferServicePort);
  }

  void ModuleHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_DELETE_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "DELETE");
    log_debug_stream(_logger) << "Transfer DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    //SetHeaders(request, region, user);
    //ForwardRequest(request, response, _transferServiceHost, _transferServicePort);
  }

  void ModuleHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_HEAD_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "HEAD");
    log_debug_stream(_logger) << "Transfer HEAD request, address: " << request.clientAddress().toString() << std::endl;

    //SetHeaders(request, region, user);
    //ForwardRequest(request, response, _transferServiceHost, _transferServicePort);
  }

  void ModuleHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_OPTIONS_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "OPTIONS");
    log_debug_stream(_logger) << "Transfer OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  std::string ModuleHandler::ToJson(const Database::Entity::Service::ServiceList &serviceList) {
    try {
      Poco::JSON::Array moduleJsonArray;
      for (const auto &service : serviceList) {
        Poco::JSON::Object serviceJson;
        serviceJson.set("name", service.name);
        serviceJson.set("executable", service.executable);
        serviceJson.set("port", service.port);
        serviceJson.set("status", Database::Entity::Service::ServiceStatusToString(service.status));
        serviceJson.set("created", Poco::DateTimeFormatter().format(service.created, Poco::DateTimeFormat::HTTP_FORMAT));
        serviceJson.set("modified", Poco::DateTimeFormatter().format(service.modified,Poco::DateTimeFormat::HTTP_FORMAT));
        moduleJsonArray.add(serviceJson);
      }

      std::ostringstream os;
      moduleJsonArray.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  std::string ModuleHandler::ToJson(const Database::Entity::Service::Service &service) {
    try {
      Poco::JSON::Object rootJson;
      rootJson.set("name", service.name);
      rootJson.set("executable", service.executable);
      rootJson.set("port", service.port);
      rootJson.set("status", Database::Entity::Service::ServiceStatusToString(service.status));
      rootJson.set("created", Poco::DateTimeFormatter().format(service.created, Poco::DateTimeFormat::HTTP_FORMAT));
      rootJson.set("modified", Poco::DateTimeFormatter().format(service.modified,Poco::DateTimeFormat::HTTP_FORMAT));

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }
}
