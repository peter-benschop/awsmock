//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_KMS_HANDLER_H
#define AWSMOCK_SERVICE_KMS_HANDLER_H

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/dto/common/KMSClientCommand.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/kms/KMSCmdHandler.h>
#include <awsmock/service/kms/KMSService.h>

namespace AwsMock::Service {

    /**
     * AWS KMS mock handler
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class KMSHandler : public KMSCmdHandler {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit KMSHandler(Core::Configuration &configuration) : KMSCmdHandler(configuration), _configuration(configuration), _kmsService(configuration) {}

        /**
         * HTTP POST request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param region AWS region
         * @param user AWS user
         * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) override;

      private:

        /**
         * ImageHandler import configuration
         */
        Core::Configuration &_configuration;

        /**
         * KMS service
         */
        Service::KMSService _kmsService;

        /**
         * Default account ID
         */
        std::string _accountId;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_HANDLER_H
