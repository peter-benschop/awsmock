
#include <awsmock/service/gateway/GatewayHandler.h>

namespace AwsMock::Service {

  GatewayHandler::GatewayHandler(Core::Configuration &configuration, Core::MetricService &metricService, std::string host, int port)
      : AbstractHandler(), _logger(Poco::Logger::get("GatewayHandler")), _configuration(configuration), _metricService(metricService), _host(std::move(host)), _port(port) {
  }

  void GatewayHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Gateway GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    Core::MetricServiceTimer measure(_metricService, GATEWAY_GET_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "GET");
    log_debug_stream(_logger) << "Gateway GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _host, _port);
  }

  void GatewayHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Gateway PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    Core::MetricServiceTimer measure(_metricService, GATEWAY_PUT_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "PUT");
    log_debug_stream(_logger) << "Gateway PUT request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _host, _port);
  }

  void GatewayHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Gateway POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    Core::MetricServiceTimer measure(_metricService, GATEWAY_POST_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "POST");
    log_debug_stream(_logger) << "Gateway POST request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _host, _port);
  }

  void GatewayHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Gateway DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    Core::MetricServiceTimer measure(_metricService, GATEWAY_DELETE_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "DELETE");
    log_debug_stream(_logger) << "Gateway DELETE request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _host, _port);
  }

  void GatewayHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Gateway HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    Core::MetricServiceTimer measure(_metricService, GATEWAY_HEAD_TIMER);
    _metricService.IncrementCounter(GATEWAY_COUNTER, "method", "HEAD");
    log_debug_stream(_logger) << "Gateway HEAD request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    SetHeaders(request, region, user);
    ForwardRequest(request, response, _host, _port);
  }

  void GatewayHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "Gateway OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void GatewayHandler::ForwardRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &host, int port) {

    // Create HTTP request and set headers
    Poco::Net::HTTPClientSession session(host, port);
    session.setReceiveTimeout(Poco::Timespan(120, 0));
    log_trace_stream(_logger) << "Forward session, host: " << host << " port: " << port << std::endl;

    // Send request with body
    Poco::StreamCopier::copyStream(request.stream(), session.sendRequest(request));
    log_trace_stream(_logger) << "Forward request send" << std::endl;

    // Get the response
    Poco::Net::HTTPResponse clientResponse;
    std::istream &is = session.receiveResponse(clientResponse);

    // Copy headers
    for (const auto &i : clientResponse) {
      response.set(i.first, i.second);
    }
    long send = Poco::StreamCopier::copyStream(is, response.send());
    log_trace_stream(_logger) << "Bytes send: " << send << std::endl;

    log_trace_stream(_logger) << "Backend module response send back to client" << std::endl;
  }

  void GatewayHandler::SetHeaders(Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Setting request header values, region: " << region << " user: " << user << std::endl;

    // Default headers
    request.set("Region", region);
    request.set("User", user);
    request.set("RequestId", Core::AwsUtils::CreateRequestId());
  }
}
