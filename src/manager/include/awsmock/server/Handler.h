//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_MANAGER_SERVER_H
#define AWSMOCK_MANAGER_SERVER_H

// C++ includes
#include <iostream>

// Boost includes
#include <boost/asio.hpp>
#include <boost/beast.hpp>

// AwsMock includes
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/monitoring/MetricDefinition.h>
#include <awsmock/core/monitoring/MetricServiceTimer.h>
#include <awsmock/dto/common/Services.h>
#include <awsmock/dto/module/GatewayConfig.h>
#include <awsmock/dto/module/Module.h>
#include <awsmock/service/common/ModuleService.h>

namespace AwsMock::Manager {

    /**
     * @brief HTTP handler
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Handler {

      public:

        /**
         * @brief Manager HTTP server
         */
        explicit Handler(Service::ServerMap &serverMap) : _serverMap(serverMap), _moduleService(serverMap){};

        /**
         * @brief Handler HTTP GET requests.
         *
         * Handles all GET requests.
         *
         * @param request HTTP request
         * @param socket HTTP socket
         * @return response structure
         */
        boost::beast::http::response<boost::beast::http::string_body> HandleGetRequest(boost::beast::http::request<boost::beast::http::string_body> &request);

        /**
         * @brief Handler HTTP PUT requests.
         *
         * Handles all PUT requests.
         *
         * @param request HTTP request
         * @param socket HTTP socket
         */
        boost::beast::http::response<boost::beast::http::string_body> HandlePutRequest(boost::beast::http::request<boost::beast::http::string_body> &request);

      private:

        /**
         * @brief Send a OK response (status=200)
         *
         * @param request HTTP request
         * @param body HTTP body
         */
        static boost::beast::http::response<boost::beast::http::string_body> SendOkResponse(boost::beast::http::request<boost::beast::http::string_body> &request, const std::string &body = {});

        /**
         * Module service
         */
        Service::ModuleService _moduleService;

        /**
         * Server nmap
         */
        Service::ServerMap _serverMap;
    };

}// namespace AwsMock::Manager

#endif//AWSMOCK_MANAGER_SERVER_H
