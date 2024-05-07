//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDA_EXECUTOR_H
#define AWSMOCK_SERVICE_LAMBDA_EXECUTOR_H

// Poco includes
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/CurlUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/MetricServiceTimer.h>

namespace AwsMock::Service {

    /**
     * AWS lambda executor. The executor is launched asynchronously.
     *
     * <p>
     * As the dockerized lambda runtime using AWS RIE only allows the execution of a lambda function at a time, the lambda function invocation will be queued up in a Poco notification queue and executed one by one. Each invocation will wait for the
     * finishing of the last invocation request. The lambda image can run on a remote docker instance. In this case the hostname on the invocation request has to be filled in. Default is 'localhost'.
     * </p>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class LambdaExecutor {

      public:

        /**
         * Send the invocation request to the corresponding port
         *
         * @param url lambda docker URL
         * @param body event payload
         */
        static void SendInvocationRequest(const std::string &url, const std::string &body);

      private:

        /**
         * Metric module
         */
        Core::MetricService &_metricService = Core::MetricService::instance();

        /**
         * Mutex
         */
        static Poco::Mutex _mutex;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_LAMBDA_EXECUTOR_H
