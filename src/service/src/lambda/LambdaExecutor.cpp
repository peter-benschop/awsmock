//
// Created by root on 10/9/23.
//

#include <awsmock/service/lambda/LambdaExecutor.h>

#include <utility>

namespace AwsMock::Service {

    Poco::Mutex LambdaExecutor::_mutex;

    void LambdaExecutor::Run() {
        Poco::ScopedLock lock(_mutex);

        Core::MetricServiceTimer measure(LAMBDA_INVOCATION_TIMER);
        Core::MetricService::instance().IncrementCounter(LAMBDA_INVOCATION_COUNT);
        log_debug << "Sending lambda invocation request, endpoint: " << _url;

        Core::CurlUtils _curlUtils;
        Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", _url, {}, _payload);
        if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_debug << "HTTP error, status: " << response.statusCode << " reason: " << response.output;
        }
        log_debug << "Lambda invocation finished send, status: " << response.statusCode;
    }
}// namespace AwsMock::Service