//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_SQS_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_SQS_HANDLER_FACTORY_H

// Poco includes
#include "Poco/Condition.h"
#include "Poco/Logger.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// AwsMock includes
#include "awsmock/core/Configuration.h"
#include "awsmock/core/MetricService.h"
#include "SQSHandler.h"

namespace AwsMock::Service {

  /**
   * S3 request handler factory
   */
  class SQSRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService  monitoring
     * @param condition stop condition
     */
    SQSRequestHandlerFactory(Core::Configuration &configuration, Core::MetricService &metricService) : _configuration(configuration), _metricService(metricService) {}

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
      return new SQSHandler(_configuration, _metricService);
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

#endif //AWSMOCK_SERVICE_SQS_HANDLER_FACTORY_H
