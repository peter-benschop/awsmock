//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/resource/factory/ServiceFactory.h"

namespace AwsMock::Resource::Factory {

    Poco::Net::HTTPRequestHandler *ServiceFactory::createResource(Core::Configuration &configuration, Core::MetricService &metricService) {
        return new ServiceHandler(configuration, metricService);
    }
}

