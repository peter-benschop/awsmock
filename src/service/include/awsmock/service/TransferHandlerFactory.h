//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_TRANSFERHANDLERFACTORY_H
#define AWSMOCK_SERVICE_TRANSFERHANDLERFACTORY_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/service/TransferHandler.h>

namespace AwsMock::Service {

  /**
   * Transfer request handler factory
   */
  class TransferRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService  monitoring
     */
    TransferRequestHandlerFactory(Core::Configuration &configuration, Core::MetricService &metricService) : _configuration(configuration), _metricService(metricService) {}

    /**
     * Create new request handler instance
     *
     * @return request handler instance
     */
    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &) override {
      return new TransferHandler(_configuration, _metricService);
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

#endif //AWSMOCK_SERVICE_TRANSFERHANDLERFACTORY_H
