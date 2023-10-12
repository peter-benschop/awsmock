//
// Created by root on 10/9/23.
//

#include <awsmock/worker/LambdaExecutor.h>

namespace AwsMock::Worker {

  LambdaExecutor::LambdaExecutor(const Core::Configuration &configuration, Core::MetricService &metricService)
      : _logger(Poco::Logger::get("LambdaExecutor")), _configuration(configuration), _metricService(metricService) {

    // Get configuration parameters
    //_notificationTimeout = _configuration.getInt("awsmock.lambda.notification.timeout", LAMBDA_NOTIFICATION_TIMEOUT);
  }

  void LambdaExecutor::HandleInvocationNotifications(Dto::Lambda::InvocationNotification *invocationNotification) {
    log_debug_stream(_logger) << "Lambda invocation notification received, name:" << invocationNotification->functionName << std::endl;
    SendInvocationRequest(invocationNotification->port, invocationNotification->payload);
    invocationNotification->release();
  }

  void LambdaExecutor::SendInvocationRequest(int port, const std::string &body) {
    Core::MetricServiceTimer measure(_metricService, "lambda_invocation_timer");
    _metricService.IncrementCounter("lambda_invocation_counter");
    log_debug_stream(_logger) << "Sending lambda invocation request, port: " << port << std::endl;

    Poco::URI uri("http://localhost:" + std::to_string(port) + "/2015-03-31/functions/function/invocations");
    std::string path(uri.getPathAndQuery());

    // Create HTTP request and set headers
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
    request.add("Content-Type", "application/json");
    request.setContentLength((long) body.length());
    log_trace_stream(_logger) << "Invocation request defined, body: " + body << std::endl;

    // Send request
    std::ostream &os = session.sendRequest(request);
    os << body;
    os.flush();

    // Get the response status
    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
      log_error_stream(_logger) << "HTTP error, status: " << response.getStatus() << " reason: " + response.getReason() << std::endl;
    }
    log_debug_stream(_logger) << "Lambda invocation request send, status: " << response.getStatus() << std::endl;
  }

}