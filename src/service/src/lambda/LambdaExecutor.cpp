//
// Created by root on 10/9/23.
//

#include <awsmock/service/lambda/LambdaExecutor.h>

namespace AwsMock::Service {

  Poco::Mutex LambdaExecutor::_mutex;

  void LambdaExecutor::SendInvocationRequest(const std::string &url, const std::string &body) {
    Poco::ScopedLock lock(_mutex);

    Core::MetricServiceTimer measure(Core::MetricService::instance(), "lambda_invocation_timer");
    Core::MetricService::instance().IncrementCounter("lambda_invocation_counter");
    Poco::Logger::get("LambdaExecutor").debug("Sending lambda invocation request, endpoint: " + url);

    Core::CurlUtils _curlUtils;
    Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", url, {}, body);
    if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
      Poco::Logger::get("LambdaExecutor").debug("HTTP error, status: " + std::to_string(response.statusCode) + " reason: " + response.output);
    }
    Poco::Logger::get("LambdaExecutor").debug("Lambda invocation finished send, status: " + std::to_string(response.statusCode));
  }
}