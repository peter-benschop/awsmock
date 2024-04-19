//
// Created by vogje01 on 07/04/2024.
//

#ifndef AWSMOCK_SERVICE_SECRETMANAGER_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_SECRETMANAGER_HANDLER_FACTORY_H

// Poco includes
#include <Poco/Net/HTTPRequestHandlerFactory.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/service/secretsmanager/SecretsManagerHandler.h>

namespace AwsMock::Service {

  /**
   * Secrets manager request handler factory
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class SecretsManagerRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService  monitoring
     */
    SecretsManagerRequestHandlerFactory(Core::Configuration &configuration, Core::MetricService &metricService) : _configuration(configuration), _metricService(metricService){}

    /**
     * Create a new request handler
     *
     * @param request HTTP request
     * @return pointer to request handler
     */
    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
      if(request.getURI().empty()) {
        return nullptr;
      }
      return new SecretsManagerHandler(_configuration, _metricService);
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

#endif //AWSMOCK_SERVICE_SECRETMANAGER_HANDLER_FACTORY_H
