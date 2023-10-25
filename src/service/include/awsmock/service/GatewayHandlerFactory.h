//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_GATEWAYHANDLERFACTORY_H
#define AWSMOCK_SERVICE_GATEWAYHANDLERFACTORY_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/service/GatewayHandler.h>

namespace AwsMock::Service {

    /**
     * S3 request handler factory
     */
    class GatewayRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

    public:

      /**
       * Constructor
       *
       * @param configuration application configuration
       * @param metricService  monitoring
       */
      GatewayRequestHandlerFactory(Core::Configuration &configuration, Core::MetricService &metricService) : _configuration(configuration), _metricService(metricService) {}

      /**
       * Creates a new request handler
       *
       * @param request HTTP request
       * @param host service host
       * @param port service port
       * @return request HTTP request handler
       */
      virtual Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request, const std::string &host, int port) {
          return new GatewayHandler(_configuration, _metricService, host, port);
      }

    private:

      /**
       * S3 handler configuration
       */
      Core::Configuration &_configuration;

      /**
       * Metric service
       */
      Core::MetricService &_metricService;

    };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_GATEWAYHANDLERFACTORY_H
