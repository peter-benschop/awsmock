
#include "awsmock/resource/handler/SNSHandler.h"

namespace AwsMock {

  SNSHandler::SNSHandler(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractResource(), _logger(Poco::Logger::get("SNSHandler")), _configuration(configuration), _metricService(metricService) {

    // Service parameter
    _snsServiceHost = _configuration.getString("awsmock.service.sns.host", "localhost");
    _snsServicePort = _configuration.getInt("awsmock.service.sns.port", 9502);
  }

  void SNSHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_GET_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "GET");
    log_debug_stream(_logger) << "SNS GET request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    DumpRequest(request);
    DumpResponse(response);
  }

  void SNSHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_PUT_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "PUT");
    log_debug_stream(_logger) << "SNS PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    DumpRequest(request);
    DumpResponse(response);
  }

  void SNSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_POST_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "POST");
    _logger.trace() << "SNS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _snsServiceHost, _snsServicePort);
  }

  void SNSHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_DELETE_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "DELETE");
    log_debug_stream(_logger) << "SNS DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    DumpRequest(request);
    DumpResponse(response);
  }

  void SNSHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_OPTIONS_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "OPTIONS");
    log_debug_stream(_logger) << "SNS OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
