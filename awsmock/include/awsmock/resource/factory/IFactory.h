//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_IFACTORY_H
#define AWSMOCK_RESOURCE_IFACTORY_H

// Poco includes
#include "Poco/Net/HTTPRequestHandler.h"

// Libri includes
#include <awsmock/core/MetricService.h>
#include <awsmock/core/Configuration.h>

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
       * @param s3Adapter AWS S3 adapter
       * @param database  database connection
       * @return HTTP request handler
       */
      virtual Poco::Net::HTTPRequestHandler *createResource(Core::Configuration &configuration,
                                                            Core::MetricService &metricService) = 0;
    };

} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_IFACTORY_H
