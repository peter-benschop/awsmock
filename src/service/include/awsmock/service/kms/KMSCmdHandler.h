//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_KMS_CMD_HANDLER_H
#define AWSMOCK_SERVICE_KMS_CMD_HANDLER_H

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/KMSClientCommand.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/kms/KMSService.h>

namespace AwsMock::Service {

    typedef std::map<std::string, std::string> AttributeList;

    /**
     * AWS KMS command handler
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class KMSCmdHandler : public virtual AbstractHandler {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit KMSCmdHandler(Core::Configuration &configuration) : AbstractHandler(), _configuration(configuration), _kmsService(configuration) {}

      protected:

        /**
         * HTTP POST request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param snsClientCommand standardised client command
         * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::KMSClientCommand &clientCommand);

      private:

        /**
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * KMS module
         */
        Service::KMSService _kmsService;

        /**
         * Default account ID
         */
        std::string _accountId;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_KMS_CMD_HANDLER_H
