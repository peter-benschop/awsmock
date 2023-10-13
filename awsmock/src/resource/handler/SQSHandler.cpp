
#include "awsmock/resource/handler/SQSHandler.h"

namespace AwsMock {

  SQSHandler::SQSHandler(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractResource(), _logger(Poco::Logger::get("SQSHandler")), _configuration(configuration), _metricService(metricService) {

    _sqsServiceHost = _configuration.getString("awsmock.service.sqs.host", "localhost");
    _sqsServicePort = _configuration.getInt("awsmock.service.sqs.port", 9501);
  }

  void SQSHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_GET_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "GET");
    log_debug_stream(_logger) << "SQS GET request, URI: " << request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_PUT_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "PUT");
    log_debug_stream(_logger) << "SQS PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_POST_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "POST");
    log_debug_stream(_logger) << "SQS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _sqsServiceHost, _sqsServicePort);
  }

  void SQSHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_DELETE_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "DELETE");
    log_debug_stream(_logger) << "SQS DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _sqsServiceHost, _sqsServicePort);
  }

  void SQSHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_OPTIONS_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "OPTIONS");
    log_debug_stream(_logger) << "SQS OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void SQSHandler::handleHead([[maybe_unused]]Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_HEAD_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "HEAD");
    log_debug_stream(_logger) << "SQS HEAD request, address: " << request.clientAddress().toString() << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _sqsServiceHost, _sqsServicePort);
  }
}
