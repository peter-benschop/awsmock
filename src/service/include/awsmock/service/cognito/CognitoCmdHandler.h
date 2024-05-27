//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITO_CMD_HANDLER_H
#define AWSMOCK_SERVICE_COGNITO_CMD_HANDLER_H

// Poco includes
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

#include <Poco/DateTime.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/dto/cognito/CreateUserPoolDomainRequest.h>
#include <awsmock/dto/cognito/CreateUserPoolDomainResponse.h>
#include <awsmock/dto/common/CognitoClientCommand.h>
#include <awsmock/service/cognito/CognitoService.h>
#include <awsmock/service/common/AbstractHandler.h>

namespace AwsMock::Service {

    /**
     * @brief Cognito HTTP handler
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CognitoCmdHandler : public virtual AbstractHandler {

      public:

        /**
         * @brief Constructor
         */
        explicit CognitoCmdHandler() : AbstractHandler() {}

      protected:

        /**
         * @brief HTTP POST request.
         *
         * This is the only handler for cognito.
         *
         * @param request HTTP request
         * @param response HTTP response
         * @param clientCommand awsmock client command
         * @see AbstractResource::handlePost(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::CognitoClientCommand &clientCommand);

      private:

        /**
         * @brief Return the command from the header.
         *
         * @param request HTTP request
         * @return SQS action
         */
        static std::string GetActionFromHeader(Poco::Net::HTTPServerRequest &request);

        /**
         * Cognito service
         */
        Service::CognitoService _cognitoService;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_COGNITO_CMD_HANDLER_H
