//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/resource/factory/LambdaFactory.h"

namespace AwsMock::Resource::Factory {

    Poco::Net::HTTPRequestHandler *LambdaFactory::createResource(Core::Configuration &configuration, Core::MetricService &metricService) {
        return new LambdaHandler(configuration, metricService);
    }
}

