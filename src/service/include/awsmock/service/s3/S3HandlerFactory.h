//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_S3_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_S3_HANDLER_FACTORY_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// AwsMock includes
#include "S3Handler.h"
#include "awsmock/core/Configuration.h"
#include "awsmock/core/MetricService.h"

namespace AwsMock::Service {

    /**
     * S3 request handler factory
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit S3RequestHandlerFactory(Core::Configuration &configuration) : _configuration(configuration) {}

        /**
         * Creates a new request handler
         *
         * @param request HTTP request
         * @return request HTTP request handler
         */
        Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
            if (request.getURI().empty()) {
                return nullptr;
            }
            return new S3Handler(_configuration);
        }

      private:

        /**
         * Configuration
         */
        Core::Configuration &_configuration;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_S3_HANDLER_FACTORY_H
