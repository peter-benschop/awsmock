//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/resource/factory/ModuleFactory.h>

namespace AwsMock::Resource::Factory {

    Poco::Net::HTTPRequestHandler *ModuleFactory::createResource(Core::Configuration &configuration, Core::MetricService &metricService) {
        return new ModuleHandler(configuration, metricService);
    }
}

