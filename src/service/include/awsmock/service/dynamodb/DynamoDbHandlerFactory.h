//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_DYNAMODB_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_DYNAMODB_HANDLER_FACTORY_H

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/ScopedLock.h>

// AwsMock includes
#include "DynamoDbHandler.h"
#include "awsmock/core/Configuration.h"
#include "awsmock/core/MetricService.h"

namespace AwsMock::Service {

    /**
     * DynamoDB request handler factory
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DynamoDbRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit DynamoDbRequestHandlerFactory(Core::Configuration &configuration) : _configuration(configuration) {}

        /**
         * Create new lambda request handler
         *
         * @param request HTTP request
         * @return lambda request handler
         */
        Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
            if (request.getURI().empty()) {
                return nullptr;
            }
            return new DynamoDbHandler(_configuration);
        }

      private:

        /**
         * S3 handler configuration
         */
        Core::Configuration &_configuration;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_DYNAMODB_HANDLER_FACTORY_H
