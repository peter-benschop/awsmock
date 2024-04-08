//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_DYNAMODB_HANDLER_FACTORY_H
#define AWSMOCK_SERVICE_DYNAMODB_HANDLER_FACTORY_H

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Mutex.h>
#include <Poco/ScopedLock.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

// AwsMock includes
#include "awsmock/core/Configuration.h"
#include "awsmock/core/MetricService.h"
#include "DynamoDbHandler.h"

namespace AwsMock::Service {

  /**
   * DynamoDB request handler factory
   */
  class DynamoDbRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

  public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService  monitoring
     */
    DynamoDbRequestHandlerFactory(Core::Configuration &configuration,
                                Core::MetricService &metricService)
        : _configuration(configuration), _metricService(metricService) {}

    /**
     * Create new lambda request handler
     *
     * @param request HTTP request
     * @return lambda request handler
     */
    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override {
      if(request.getURI().empty()) {
        return nullptr;
      }
      return new DynamoDbHandler(_configuration, _metricService);
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

#endif // AWSMOCK_SERVICE_DYNAMODB_HANDLER_FACTORY_H
