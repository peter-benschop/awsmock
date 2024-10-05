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
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/Services.h>
#include <awsmock/dto/module/GatewayConfig.h>
#include <awsmock/dto/module/Module.h>
#include <awsmock/monitoring/MetricDefinition.h>
#include <awsmock/monitoring/MetricServiceTimer.h>
#include <awsmock/service/module/ModuleService.h>

namespace AwsMock::Service {

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
        explicit ModuleHandler(Service::ServerMap &serverMap) : _serverMap(serverMap), _moduleService(serverMap) {};

        /**
         * @brief Handler HTTP GET requests.
         *
         * Handles all GET requests.
         *
         * @param request HTTP request
         * @return HTTP response structure
         */
        boost::beast::http::response<boost::beast::http::dynamic_body> HandleGetRequest(boost::beast::http::request<boost::beast::http::dynamic_body> &request);

        /**
         * @brief Handler HTTP POST requests.
         *
         * Handles all POST requests.
         *
         * @param request HTTP request
         * @return HTTP response structure
         */
        boost::beast::http::response<boost::beast::http::dynamic_body> HandlePostRequest(boost::beast::http::request<boost::beast::http::dynamic_body> &request);

      private:

        /**
         * Module service
         */
        ModuleService _moduleService;

        /**
         * Server nmap
         */
        ServerMap _serverMap;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_MODULE_HANDLER_H
