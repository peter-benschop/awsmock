//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_KMS_HANDLER_H
#define AWSMOCK_SERVICE_KMS_HANDLER_H

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/dto/common/KMSClientCommand.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/kms/KMSService.h>

namespace AwsMock::Service {

    namespace http = http;
    namespace ip = boost::asio::ip;

    /**
     * @brief KMS request handler
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class KMSHandler : public AbstractHandler {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit KMSHandler() : _kmsService(Core::Configuration::instance()) {}

        /**
         * HTTP POST request.
         *
         * @param request HTTP request
         * @param region AWS region
         * @param user AWS user
         * @return HTTP response
         * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        http::response<http::string_body> HandlePostRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) override;

      private:

        /**
         * KMS service
         */
        Service::KMSService _kmsService;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_HANDLER_H
