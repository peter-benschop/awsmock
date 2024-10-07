//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_SERVICE_MODULE_HANDLER_H
#define AWSMOCK_SERVICE_MODULE_HANDLER_H

// C++ includes
#include <iostream>

// Boost includes
#include <boost/asio.hpp>
#include <boost/beast.hpp>

// AwsMock includes
#include "awsmock/dto/module/model/GatewayConfig.h"
#include "awsmock/dto/module/model/Module.h"
#include "awsmock/service/monitoring/MetricDefinition.h"
#include "awsmock/service/monitoring/MetricServiceTimer.h"
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/Services.h>
#include <awsmock/dto/transfer/ListUsersRequest.h>
#include <awsmock/dto/transfer/model/Server.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/module/ModuleService.h>
#include <awsmock/service/transfer/TransferService.h>

namespace AwsMock::Service {

    namespace http = boost::beast::http;

    /**
     * @brief HTTP handler
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class ModuleHandler : public AbstractHandler {

      public:

        /**
         * @brief Manager HTTP server
         *
         * @param serverMap currently running servers
         */
        explicit ModuleHandler() = default;

        /**
         * @brief Handler HTTP GET requests.
         *
         * Handles all GET requests.
         *
         * @param request HTTP request
         * @return HTTP response structure
         */
        http::response<http::dynamic_body> HandleGetRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) override;

        /**
         * @brief Handler HTTP POST requests.
         *
         * Handles all POST requests.
         *
         * @param request HTTP request
         * @return HTTP response structure
         */
        http::response<http::dynamic_body> HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user);

      private:

        /**
         * Module service
         */
        ModuleService _moduleService;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_MODULE_HANDLER_H
