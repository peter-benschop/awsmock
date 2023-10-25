//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_IFACTORY_H
#define AWSMOCK_RESOURCE_IFACTORY_H

// Poco includes
#include "Poco/Net/HTTPRequestHandler.h"

// AwsMock includes
#include <awsmock/core/MetricService.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/service/AbstractServer.h>

namespace AwsMock::Resource::Factory {

    /**
     * Factory interface
     */
    class IFactory {

    public:

      /**
       * Create a new resource.
       *
       * @param configuration configuration
       * @param metricService monitoring
       * @return HTTP request handler
       */
      virtual Poco::Net::HTTPRequestHandler *createResource(Core::Configuration &configuration, Core::MetricService &metricService, Service::ServerMap &serverMap) = 0;
    };

} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_IFACTORY_H
