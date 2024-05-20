//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_KMS_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_KMS_HANDLER_FACTORY_H

// Poco includes
#include <Poco/Net/HTTPRequestHandlerFactory.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/service/kms/KMSHandler.h>

namespace AwsMock::Service {

    /**
     * @brief KMS request handler factory
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class KMSRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit KMSRequestHandlerFactory(Core::Configuration &configuration) : _configuration(configuration) {}

        /**
         * Create request handler
         *
         * @param request request HTTP request
         * @return pointer to request handler
         */
        Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
            if (request.getURI().empty()) {
                return nullptr;
            }
            return new KMSHandler(_configuration);
        }

      private:

        /**
         * S3 handler configuration
         */
        Core::Configuration &_configuration;
    };

}// namespace AwsMock::Service

#endif//AWSMOCK_SERVICE_KMS_HANDLER_FACTORY_H
