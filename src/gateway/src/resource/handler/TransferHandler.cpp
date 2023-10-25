
#include "awsmock/resource/handler/TransferHandler.h"

namespace AwsMock {

  TransferHandler::TransferHandler(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractResource(), _logger(Poco::Logger::get("TransferHandler")), _configuration(configuration), _metricService(metricService) {

    _transferServiceHost = _configuration.getString("awsmock.service.transfer.host", TRANSFER_DEFAULT_HOST);
    _transferServicePort = _configuration.getInt("awsmock.service.transfer.port", TRANSFER_DEFAULT_PORT);
  }

  void TransferHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    Core::MetricServiceTimer measure(_metricService, GATEWAY_GET_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "GET");
    log_debug_stream(_logger) << "Transfer GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _transferServiceHost, _transferServicePort);
  }

  void TransferHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_PUT_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "PUT");
    log_debug_stream(_logger) << "Transfer PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _transferServiceHost, _transferServicePort);
  }

  void TransferHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_POST_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "POST");
    log_debug_stream(_logger) << "Transfer POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _transferServiceHost, _transferServicePort);
  }

  void TransferHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_DELETE_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "DELETE");
    log_debug_stream(_logger) << "Transfer DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _transferServiceHost, _transferServicePort);
  }

  void TransferHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_HEAD_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "HEAD");
    log_debug_stream(_logger) << "Transfer HEAD request, address: " << request.clientAddress().toString() << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _transferServiceHost, _transferServicePort);
  }

  void TransferHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    Core::MetricServiceTimer measure(_metricService, GATEWAY_OPTIONS_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "OPTIONS");
    log_debug_stream(_logger) << "Transfer OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
