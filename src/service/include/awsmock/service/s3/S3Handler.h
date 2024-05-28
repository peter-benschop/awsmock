//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_S3_HANDLER_H
#define AWSMOCK_SERVICE_S3_HANDLER_H

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// Boost includes
#include <boost/beast.hpp>
#include <boost/beast/http/impl/message.hpp>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/NumberUtils.h>
#include <awsmock/core/monitoring/MetricDefinition.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/dto/common/S3ClientCommand.h>
#include <awsmock/dto/common/UserAgent.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/s3/S3CmdHandler.h>
#include <awsmock/service/s3/S3Service.h>

namespace AwsMock::Service {

    namespace http = boost::beast::http;
    namespace ip = boost::asio::ip;

    /**
     * @brief S3 request handler
     *
     * AWS S3 HTTP request handler. All S3 related REST call are ending here. Depending on the request header the S3 module will be selected in case the
     * authorization header contains the S3 module. As the different clients (Java, C++, Python, nodejs20) are using different request structure, the request
     * are first send to the S3CmdHandler, which normalizes the commands.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3Handler : public AbstractHandler {

      public:

        /**
         * Constructor
         */
        explicit S3Handler() = default;

        /**
         * HTTP GET request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handleGet(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        boost::beast::http::response<boost::beast::http::string_body> HandleGetRequest(boost::beast::http::request<boost::beast::http::string_body> &request, const std::string &region, const std::string &user);

        /**
         * HTTP PUT request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handlePut(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        boost::beast::http::response<boost::beast::http::string_body> HandlePutRequest(boost::beast::http::request<boost::beast::http::string_body> &request, const std::string &region, const std::string &user);

        /**
         * HTTP POST request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

        /**
         * Delete DELETE request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handleDelete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

        /**
         * Head request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region name
         * @param user AWS user
         * @see AbstractResource::handleHead(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

        http::response<http::string_body> SendOkResponse(http::request<http::string_body> &request, const std::string &body);

      private:

        /**
         * S3 service
         */
        S3Service _s3Service;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_S3_HANDLER_H
