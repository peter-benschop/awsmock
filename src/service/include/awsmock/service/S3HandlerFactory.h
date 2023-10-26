//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_S3HANDLERFACTORY_H
#define AWSMOCK_SERVICE_S3HANDLERFACTORY_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/service/S3Handler.h>

namespace AwsMock::Service {

  /**
   * S3 request handler factory
   */
  class S3RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

    public:

      /**
       * Constructor
       *
       * @param configuration application configuration
       * @param metricService  monitoring
       */
      S3RequestHandlerFactory(Core::Configuration &configuration, Core::MetricService &metricService) : _configuration(configuration), _metricService(metricService) {}

      /**
       * Creates a new request handler
       *
       * @param request HTTP request
       * @return request HTTP request handler
       */
      Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &) override {
        return new S3Handler(_configuration, _metricService);
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

#endif //AWSMOCK_SERVICE_S3HANDLERFACTORY_H
