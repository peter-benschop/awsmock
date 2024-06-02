//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_SERVICE_GATEWAY_HANDLER_H
#define AWSMOCK_SERVICE_GATEWAY_HANDLER_H

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

namespace AwsMock::Service {

    namespace http = boost::beast::http;

    /**
     * @brief HTTP handler
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class GatewayHandler {

      public:

        /**
         * @brief Manager HTTP server
         */
        explicit GatewayHandler() = default;

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
         * @brief Handler HTTP PUT requests.
         *
         * Handles all PUT requests.
         *
         * @param request HTTP request
         * @return HTTP response structure
         */
        boost::beast::http::response<boost::beast::http::dynamic_body> HandlePutRequest(boost::beast::http::request<boost::beast::http::dynamic_body> &request);

        /**
         * @brief Handler HTTP POST requests.
         *
         * Handles all POST requests.
         *
         * @param request HTTP request
         * @return HTTP response structure
         */
        boost::beast::http::response<boost::beast::http::dynamic_body> HandlePostRequest(boost::beast::http::request<boost::beast::http::dynamic_body> &request);

        /**
         * @brief Handler HTTP DELETE requests.
         *
         * Handles all DELETE requests.
         *
         * @param request HTTP request
         * @return HTTP response structure
         */
        boost::beast::http::response<boost::beast::http::dynamic_body> HandleDeleteRequest(boost::beast::http::request<boost::beast::http::dynamic_body> &request);

        /**
         * @brief Handler HTTP HEAD requests.
         *
         * Handles all HEAD requests.
         *
         * @param request HTTP request
         * @return HTTP response structure
         */
        boost::beast::http::response<boost::beast::http::dynamic_body> HandleHeadRequest(boost::beast::http::request<boost::beast::http::dynamic_body> &request);

      private:

        /**
         * @brief Send a OK response (status=200)
         *
         * @param request HTTP request
         * @param body HTTP body
         * @return HTTP response
         */
        static boost::beast::http::response<boost::beast::http::dynamic_body> SendOkResponse(boost::beast::http::request<boost::beast::http::dynamic_body> &request, const std::string &body = {});
    };

}// namespace AwsMock::Service

#endif//AWSMOCK_SERVICE_GATEWAY_HANDLER_H
