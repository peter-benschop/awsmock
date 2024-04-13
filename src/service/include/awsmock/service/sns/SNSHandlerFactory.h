//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_SNSHANDLERFACTORY_H
#define AWSMOCK_SERVICE_SNSHANDLERFACTORY_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// AwsMock includes
#include "awsmock/core/Configuration.h"
#include "awsmock/core/MetricService.h"
#include "SNSHandler.h"

namespace AwsMock::Service {

  /**
   * S3 request handler factory
   */
  class SNSRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService  monitoring
     * @param condition stop condition
     */
    SNSRequestHandlerFactory(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition) : _configuration(configuration), _metricService(metricService), _condition(condition) {}

    /**
     * Create request handler
     *
     * @param request request HTTP request
     * @return pointer to request handler
     */
    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
      if(request.getURI().empty()) {
        return nullptr;
      }
      return new SNSHandler(_configuration, _metricService);
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

#endif //AWSMOCK_SERVICE_SNSHANDLERFACTORY_H
