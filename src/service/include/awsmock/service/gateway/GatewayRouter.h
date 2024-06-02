//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_GATEWAY_ROUTER_H
#define AWSMOCK_SERVICE_GATEWAY_ROUTER_H

// C++ standard includes
#include <iostream>
#include <map>
#include <string>
#include <utility>

// Poco includes
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/URI.h>

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include <awsmock/core/LogStream.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/service/gateway/GatewayHandlerOld.h>
#include <awsmock/service/gateway/GatewayRoute.h>
#include <awsmock/service/lambda/LambdaCreator.h>
#include <awsmock/service/lambda/LambdaExecutor.h>

namespace AwsMock::Service {

    /**
     * @brief Gateway router
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class GatewayRouter : public Poco::Net::HTTPRequestHandlerFactory {

      public:

        /**
         * Constructor
         *
         * @param configuration application configuration
         * @param metricService common monitoring module
         */
        GatewayRouter(Core::Configuration &configuration, Core::MetricService &metricService);

        /**
         * Destructor
         */
        ~GatewayRouter() override;

        /**
         * HTTP request handler
         *
         * @param request HTTP request
         * @return request handler or null in case of failure
         */
        Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;

      private:

        /**
         * Return HTTP restful resource.
         *
         * @param service AWS module name
         * @param uri request URI
         * @return restfull resource
         */
        Poco::Net::HTTPRequestHandler *GetResource(const std::string &service, const std::string &uri);

        /**
         * Returns the AWS module, region and user from the authorization string.
         *
         * @param authInfo authorization string
         * @return module name
         */
        static std::string GetService(const std::string &authInfo);

        /**
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * Metric module
         */
        Core::MetricService &_metricService;

        /**
         * Routing table
         */
        std::map<std::string, GatewayRoute> _routingTable;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_GATEWAY_ROUTER_H
