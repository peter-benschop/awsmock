//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/resource/factory/SNSFactory.h"

namespace AwsMock::Resource::Factory {

    Poco::Net::HTTPRequestHandler *SNSFactory::createResource(Core::Configuration &configuration, Core::MetricService &metricService) {
        return new SNSHandler(configuration, metricService);
    }
}

