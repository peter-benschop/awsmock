//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITO_HANDLER_H
#define AWSMOCK_SERVICE_COGNITO_HANDLER_H

// Boost includes
#include <boost/beast.hpp>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/exception/BadRequestException.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/dto/common/CognitoClientCommand.h>
#include <awsmock/service/cognito/CognitoService.h>
#include <awsmock/service/common/AbstractHandler.h>

namespace AwsMock::Service {

    namespace http = boost::beast::http;
    namespace ip = boost::asio::ip;

    /**
     * @brief Cognito HTTP handler
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CognitoHandler : public AbstractHandler {

      public:

        /**
         * @brief Constructor
         */
        CognitoHandler() = default;

        /**
         * @brief HTTP POST request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        http::response<http::string_body> HandlePostRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) override;

      private:

        /**
         * @brief Return the command from the header.
         *
         * @param request HTTP request
         * @return Cognito action
         */
        static std::string GetActionFromHeader(const http::request<http::string_body> &request);

        /**
         * Cognito service
         */
        Service::CognitoService _cognitoService;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_COGNITO_HANDLER_H
