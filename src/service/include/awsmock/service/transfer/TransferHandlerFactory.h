//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_TRANSFER_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_TRANSFER_HANDLER_FACTORY_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// AwsMock includes
#include "TransferHandler.h"
#include "awsmock/core/Configuration.h"
#include "awsmock/core/MetricService.h"

namespace AwsMock::Service {

    /**
     * Transfer request handler factory
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class TransferRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit TransferRequestHandlerFactory(Core::Configuration &configuration) : _configuration(configuration) {}

        /**
         * Create new request handler instance
         *
         * @param request HTTP request
         * @return request handler instance pointer
         */
        Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
            if (request.getURI().empty()) {
                return nullptr;
            }
            return new TransferHandler(_configuration);
        }

      private:

        /**
         * S3 handler configuration
         */
        Core::Configuration &_configuration;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_TRANSFER_HANDLER_FACTORY_H
