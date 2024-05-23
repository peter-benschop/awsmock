//
// Created by vogje01 on 07/04/2024.
//

#ifndef AWSMOCK_SERVICE_SECRETMANAGER_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_SECRETMANAGER_HANDLER_FACTORY_H

// Poco includes
#include <Poco/Net/HTTPRequestHandlerFactory.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/service/secretsmanager/SecretsManagerHandler.h>

namespace AwsMock::Service {

    /**
     * Secrets manager request handler factory
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SecretsManagerRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit SecretsManagerRequestHandlerFactory(Core::Configuration &configuration) : _configuration(configuration) {}

        /**
         * Create a new request handler
         *
         * @param request HTTP request
         * @return pointer to request handler
         */
        Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
            if (request.getURI().empty()) {
                return nullptr;
            }
            return new SecretsManagerHandler(_configuration);
        }

      private:

        /**
         * Configuration
         */
        Core::Configuration &_configuration;
    };

}// namespace AwsMock::Service

#endif//AWSMOCK_SERVICE_SECRETMANAGER_HANDLER_FACTORY_H
