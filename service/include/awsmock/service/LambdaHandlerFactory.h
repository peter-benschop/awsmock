//
// Created by vogje01 on 17/06/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDAHANDLERFACTORY_H
#define AWSMOCK_SERVICE_LAMBDAHANDLERFACTORY_H

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/NotificationCenter.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/service/LambdaHandler.h>

namespace AwsMock::Service {

  /**
   * Lambda request handler factory
   */
  class LambdaRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

    public:

    /**
     * Constructor
     *
     * @param configuration application configuration
     * @param metricService  monitoring
     */
    LambdaRequestHandlerFactory(Core::Configuration &configuration, Core::MetricService &metricService, Poco::NotificationCenter &notificationCenter) : _configuration(configuration), _metricService(metricService), _notificationCenter(notificationCenter) {}

    /**
     * Create new lambda request handler
     *
     * @return lambda request handler
     */
    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &) override {
      return new LambdaHandler(_configuration, _metricService, _notificationCenter);
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

    /**
     * Notification center
     */
    Poco::NotificationCenter &_notificationCenter;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_LAMBDAHANDLERFACTORY_H
