//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_SQS_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_SQS_HANDLER_FACTORY_H

// Poco includes
#include <Poco/Net/HTTPRequestHandlerFactory.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/service/sqs/SQSHandler.h>

namespace AwsMock::Service {

    /**
     * SQS request handler factory
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit SQSRequestHandlerFactory(Core::Configuration &configuration) : _configuration(configuration) {}

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
            return new SQSHandler(_configuration);
        }

      private:

        /**
         * SQS handler configuration
         */
        Core::Configuration &_configuration;
    };

}// namespace AwsMock::Service

#endif//AWSMOCK_SERVICE_SQS_HANDLER_FACTORY_H
