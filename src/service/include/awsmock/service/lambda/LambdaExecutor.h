//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDA_EXECUTOR_H
#define AWSMOCK_SERVICE_LAMBDA_EXECUTOR_H

// C++ include
#include <utility>

// AwsMock includes
#include <awsmock/core/HttpSocket.h>
#include <awsmock/core/HttpSocketResponse.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Task.h>
#include <awsmock/monitoring/MetricDefinition.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/monitoring/MetricServiceTimer.h>
#include <awsmock/repository/LambdaDatabase.h>

namespace AwsMock::Service {

    namespace http = boost::beast::http;

    /**
     * @brief Lambda executor.
     *
     * The executor is launched asynchronously. As the dockerized lambda runtime using AWS RIE only allows the execution of a lambda function at a time, the lambda function invocation will be
     * queued up in a Poco notification queue and executed one by one. Each invocation will wait for the finishing of the last invocation request. The lambda image can run on a remote docker
     * instance. In this case the hostname on the invocation request has to be filled in. Default is 'localhost'.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class LambdaExecutor {

      public:

        /**
         * @brief Constructor
         */
        explicit LambdaExecutor() = default;


        /**
         * @brief Executes a lambda function
         *
         * @param function lambda function name
         * @param containerId lambda docker container ID
         * @param host lambda docker host
         * @param port lambda docker port
         * @param payload lambda payload
         */
        void operator()(const std::string &function, const std::string &containerId, const std::string &host, int port, const std::string &payload);

      private:

        /**
         * Metric module
         */
        Monitoring::MetricService &_metricService = Monitoring::MetricService::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_LAMBDA_EXECUTOR_H
