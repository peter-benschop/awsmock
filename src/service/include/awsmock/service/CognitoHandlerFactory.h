//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITOHANDLERFACTORY_H
#define AWSMOCK_SERVICE_COGNITOHANDLERFACTORY_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/service/CognitoHandler.h>

namespace AwsMock::Service {

    /**
     * S3 request handler factory
     */
    class CognitoRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

    public:

      /**
       * Constructor
       *
       * @param configuration application configuration
       * @param metricService  monitoring
       */
      CognitoRequestHandlerFactory(Core::Configuration &configuration, Core::MetricService &metricService) : _configuration(configuration), _metricService(metricService) {}

      /**
       * Create a new request handler instance.
       *
       * @param request HTTP request
       * @return HTTP request handler
       */
      virtual Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) {
          return new S3Handler(_configuration, _metricService);
      }

    private:

      /**
       * S3 handler configuration
       */
      Core::Configuration &_configuration;

      /**
       * Metric module
       */
      Core::MetricService &_metricService;

    };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_COGNITOHANDLERFACTORY_H
