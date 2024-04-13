
#include <awsmock/service/gateway/GatewayHandler.h>

namespace AwsMock::Service {

  GatewayHandler::GatewayHandler(Core::Configuration &configuration, Core::MetricService &metricService, Service::GatewayRoute* route)
    : AbstractHandler(), _logger(Poco::Logger::get("GatewayHandler")), _configuration(configuration), _metricService(metricService), _route(route) {
  }

  void GatewayHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Gateway GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    Core::MetricServiceTimer measure(_metricService, GATEWAY_GET_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "GET");
    log_debug_stream(_logger) << "Gateway GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    _route->_handler->handleRequest(request, response);
  }

  void GatewayHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Gateway PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    Core::MetricServiceTimer measure(_metricService, GATEWAY_PUT_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "PUT");
    log_debug_stream(_logger) << "Gateway PUT request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    _route->_handler->handleRequest(request, response);
  }

  void GatewayHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Gateway POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    Core::MetricServiceTimer measure(_metricService, GATEWAY_POST_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "POST");
    log_debug_stream(_logger) << "Gateway POST request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    _route->_handler->handleRequest(request, response);
  }

  void GatewayHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Gateway DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    Core::MetricServiceTimer measure(_metricService, GATEWAY_DELETE_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "DELETE");
    log_debug_stream(_logger) << "Gateway DELETE request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    _route->_handler->handleRequest(request, response);
  }

  void GatewayHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Gateway HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    Core::MetricServiceTimer measure(_metricService, GATEWAY_HEAD_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "HEAD");
    log_debug_stream(_logger) << "Gateway HEAD request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    _route->_handler->handleRequest(request, response);
  }

  void GatewayHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "Gateway OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void GatewayHandler::SetHeaders(Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Setting request header values, region: " << region << " user: " << user << std::endl;

    // Default headers
    request.set("Region", region);
    request.set("User", user);
    request.set("RequestId", Core::AwsUtils::CreateRequestId());
  }
}
