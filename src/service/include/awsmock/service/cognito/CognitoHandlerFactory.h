//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITO_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_COGNITO_HANDLER_FACTORY_H

// Poco includes
#include <Poco/Net/HTTPRequestHandlerFactory.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/service/cognito/CognitoHandler.h>

namespace AwsMock::Service {

    /**
     * @brief Cognito request handler factory
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CognitoHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

      public:

        /**
         * Constructor
         */
        CognitoHandlerFactory() = default;

        /**
         * Create a new request handler instance.
         *
         * @param request HTTP request
         * @return HTTP request handler
         */
        Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
            if (request.getURI().empty()) {
                return nullptr;
            }
            return new CognitoHandler();
        }
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_COGNITO_HANDLER_FACTORY_H
