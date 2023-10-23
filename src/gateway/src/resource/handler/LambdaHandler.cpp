
#include "awsmock/resource/handler/LambdaHandler.h"

namespace AwsMock {

  LambdaHandler::LambdaHandler(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractResource(), _logger(Poco::Logger::get("LambdaHandler")), _configuration(configuration), _metricService(metricService) {

    _lambdaServiceHost = _configuration.getString("awsmock.service.lambda.host", "localhost");
    _lambdaServicePort = _configuration.getInt("awsmock.service.lambda.port", 9503);
  }

  void LambdaHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_GET_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "HEAD");
    log_debug_stream(_logger) << "lambda GET request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _lambdaServiceHost, _lambdaServicePort);
  }

  void LambdaHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_PUT_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "PUT");
    log_debug_stream(_logger) << "lambda PUT request, URI: " << request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _lambdaServiceHost, _lambdaServicePort);
  }

  void LambdaHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_POST_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "POST");
    log_debug_stream(_logger) << "lambda POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _lambdaServiceHost, _lambdaServicePort);
  }

  void LambdaHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_DELETE_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "DELETE");
    log_debug_stream(_logger) << "lambda DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    SetHeaders(request, region, user);
    ForwardRequest(request, response, _lambdaServiceHost, _lambdaServicePort);
  }

  void LambdaHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_OPTIONS_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "OPTIONS");
    log_debug_stream(_logger) << "lambda OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void LambdaHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_HEAD_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "HEAD");
    log_debug_stream(_logger) << "lambda HEAD request, address: " << request.clientAddress().toString() << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _lambdaServiceHost, _lambdaServicePort);
  }
}
