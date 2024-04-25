//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_TRANSFER_HANDLER_H
#define AWSMOCK_SERVICE_TRANSFER_HANDLER_H


// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/service/common/AbstractHandler.h>
#include <awsmock/service/transfer/TransferService.h>

namespace AwsMock::Service {

    /**
     * AWS Transfer mock handler
     *
     * <p>AWS Transfer HTTP request handler. All Transfer related REST call are ending here.<p>
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class TransferHandler : public AbstractHandler {

      public:
        /**
         * Constructor
         *
         * @param configuration application configuration
         */
        explicit TransferHandler(Core::Configuration &configuration) : AbstractHandler(), _configuration(configuration), _transferService(configuration) {}

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
         * Get the request target.
         *
         * @param request HTTP request
         * @return target string
         */
        static std::string GetTarget(const Poco::Net::HTTPServerRequest &request);

        /**
         * Transfer handler configuration
         */
        Core::Configuration &_configuration;

        /**
         * Transfer module
         */
        Service::TransferService _transferService;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_TRANSFER_HANDLER_H
