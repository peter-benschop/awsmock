//
// Created by root on 10/9/23.
//

#include <awsmock/service/lambda/LambdaExecutor.h>

namespace AwsMock::Service {

    void LambdaExecutor::Run() {

        Core::MetricServiceTimer measure(LAMBDA_INVOCATION_TIMER);
        Core::MetricService::instance().IncrementCounter(LAMBDA_INVOCATION_COUNT);
        log_debug << "Sending lambda invocation request, endpoint: " << _host << ":" << _port;

        Core::HttpSocketResponse response = Core::HttpSocket::SendJson(http::verb::post, _host, _port, "/2015-03-31/functions/function/invocations", _payload, {});
        if (response.statusCode != http::status::ok) {
            log_debug << "HTTP error, httpStatus: " << response.statusCode << " body: " << response.body;
        }
        log_debug << "Lambda invocation finished send, httpStatus: " << response.statusCode;
        log_info << "Lambda output: " << response.body;
    }

}// namespace AwsMock::Service