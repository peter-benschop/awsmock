//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_S3_CMD_HANDLER_H
#define AWSMOCK_SERVICE_S3_CMD_HANDLER_H

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/NumberUtils.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/dto/common/S3ClientCommand.h>
#include <awsmock/dto/common/UserAgent.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/s3/S3Service.h>

namespace AwsMock::Service {

    /**
     * @brief S3 command handler
     *
     * S3 HTTP request handler. All S3 related REST call are ending here. Depending on the request header the S3 module will be selected in case the
     * authorization header contains the S3 module. As the different clients (Java, C++, Python, nodejs20) are using different request structure, the request
     * are first send to the S3CmdHandler, which normalizes the commands.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3CmdHandler : public virtual AbstractHandler {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit S3CmdHandler(Core::Configuration &configuration) : AbstractHandler(), _configuration(configuration), _s3Service(configuration) {}

      protected:

        /**
         * HTTP GET request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param s3Command S3 client command
         * @see AbstractResource::handleGet(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3Command) override;

        /**
         * HTTP PUT request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param s3Command S3 client command
         * @see AbstractResource::handlePut(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3Command) override;

        /**
         * HTTP POST request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param s3Command S3 client command
         * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3Command) override;

        /**
         * Delete DELETE request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param s3Command S3 client command
         * @see AbstractResource::handleDelete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3Command) override;

        /**
         * Head request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param s3Command S3 client command
         * @see AbstractResource::handleHead(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3Command) override;

      private:

        /**
         * Handler configuration
         */
        Core::Configuration &_configuration;

        /**
         * S3 service
         */
        Service::S3Service _s3Service;

        /**
         * Metric service
         */
        Core::MetricService &_metricService = Core::MetricService::instance();
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_S3_CMD_HANDLER_H
