//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITO_CLI_HANDLER_H
#define AWSMOCK_SERVICE_COGNITO_CLI_HANDLER_H

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/service/cognito/CognitoService.h>
#include <awsmock/service/common/AbstractHandler.h>

namespace AwsMock::Service {

    /**
     * Cognito command line handler
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CognitoCliHandler : public virtual AbstractHandler {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit CognitoCliHandler(Core::Configuration &configuration) : AbstractHandler(), _configuration(configuration), _cognitoService(configuration){};

      protected:

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

      private:

        /**
         * AwsMock configuration
         */
        Core::Configuration &_configuration;

        /**
         * Cognito service
         */
        Service::CognitoService _cognitoService;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_COGNITO_CLI_HANDLER_H
