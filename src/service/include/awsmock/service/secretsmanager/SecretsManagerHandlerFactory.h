//
// Created by vogje01 on 07/04/2024.
//

#ifndef AWSMOCK_SERVICE_SECRETMANAGER_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_SECRETMANAGER_HANDLER_FACTORY_H

// Poco includes
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/service/secretsmanager/SecretsManagerHandler.h>

namespace AwsMock::Service {

  /**
   * S3 request handler factory
   */
  class SecretsManagerRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService  monitoring
     * @param condition stop condition
     */
    SecretsManagerRequestHandlerFactory(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition) : _configuration(configuration), _metricService(metricService), _condition(condition) {}

    /**
     * Create a new request handler
     *
     * @request request HTTP request
     * @return new request handler
     */
    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
      if(request.getURI().empty()) {
        return nullptr;
      }
      return new SecretsManagerHandler(_configuration, _metricService, _condition);
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

    /**
     * Shutdown condition
     */
    Poco::Condition &_condition;
  };

} // namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_SECRETMANAGER_HANDLER_FACTORY_H
