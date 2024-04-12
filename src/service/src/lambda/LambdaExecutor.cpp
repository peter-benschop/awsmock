//
// Created by root on 10/9/23.
//

#include "awsmock/service/lambda/LambdaExecutor.h"

namespace AwsMock::Service {

  LambdaExecutor::LambdaExecutor(Core::MetricService &metricService, Poco::NotificationQueue &invokeQueue) : Core::Timer("LambdaExecutor", 1), _logger(Poco::Logger::get("LambdaExecutor")), _metricService(metricService), _invokeQueue(invokeQueue) {}

  void LambdaExecutor::Initialize() {
  }

  void LambdaExecutor::Run() {
    log_debug_stream(_logger) << "lambda invocation notification received, queueSize:" << _invokeQueue.size() << std::endl;
    Poco::AutoPtr<Poco::Notification> pNf(_invokeQueue.waitDequeueNotification());
    auto *pWorkNf = dynamic_cast<Dto::Lambda::InvocationNotification *>(pNf.get());
    if (pWorkNf) {
      SendInvocationRequest(pWorkNf->hostName, pWorkNf->port, pWorkNf->payload);
    }
  }

  void LambdaExecutor::Shutdown() {
  }

  void LambdaExecutor::SendInvocationRequest(const std::string &hostName, int port, const std::string &body) {
    Core::MetricServiceTimer measure(_metricService, "lambda_invocation_timer");
    _metricService.IncrementCounter("lambda_invocation_counter");
    log_debug_stream(_logger) << "Sending lambda invocation request, endpoint: " << hostName << ":" << port << std::endl;

    Poco::URI uri = GetRequestUri(hostName, port);
    std::string path(uri.getPathAndQuery());
    log_debug_stream(_logger) << "Created URI, endpoint: " << path << std::endl;

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

    // Get the response state
    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
      log_error_stream(_logger) << "HTTP error, state: " << response.getStatus() << " reason: " + response.getReason() << std::endl;
    }
    log_debug_stream(_logger) << "lambda invocation request send, state: " << response.getStatus() << std::endl;
  }

  Poco::URI LambdaExecutor::GetRequestUri(const std::string &hostName, int port) {
    if (hostName.empty()) {
      return Poco::URI("http://localhost:" + std::to_string(port) + "/2015-03-31/functions/function/invocations");
    }
    return Poco::URI("http://" + hostName + ":" + std::to_string(port) + "/2015-03-31/functions/function/invocations");
  }
}