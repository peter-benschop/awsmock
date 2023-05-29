//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/resource/factory/SQSFactory.h"

namespace AwsMock::Resource::Factory {

    Poco::Net::HTTPRequestHandler *SQSFactory::createResource(Core::Configuration &configuration, Core::MetricService &metricService) {
        return new SQSHandler(configuration, metricService);
    }
}

