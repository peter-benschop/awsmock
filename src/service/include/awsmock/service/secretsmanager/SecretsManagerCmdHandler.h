//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_SECRETSMANAGER_CMD_HANDLER_H
#define AWSMOCK_SERVICE_SECRETSMANAGER_CMD_HANDLER_H

// Poco includes
#include <Poco/Condition.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// AwsMock includes
#include "awsmock/service/monitoring/MetricService.h"
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/dto/common/SecretsManagerClientCommand.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/secretsmanager/SecretsManagerService.h>

#define DEFAULT_SQS_ACCOUNT_ID "000000000000"

namespace AwsMock::Service {

    /**
     * UserAttribute  list
     */
    typedef std::map<std::string, std::string> AttributeList;

    /**
     * AWS Secrets manager mock handler.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SecretsManagerCmdHandler : public virtual AbstractHandler {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit SecretsManagerCmdHandler(Core::Configuration &configuration);

      protected:

        /**
         * HTTP POST request.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param sqsClientCommand standardised client command
         * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::SecretsManagerClientCommand &sqsClientCommand);

      private:

        /**
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * Secrets manager module
         */
        Service::SecretsManagerService _secretsManagerService;

        /**
         * Default account ID
         */
        std::string _accountId;

        /**
         * Default endpoint
         */
        std::string _endpoint;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_SECRETSMANAGER_CMD_HANDLER_H
