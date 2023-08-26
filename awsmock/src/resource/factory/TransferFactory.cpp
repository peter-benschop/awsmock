//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/resource/factory/TransferFactory.h"

namespace AwsMock::Resource::Factory {

    Poco::Net::HTTPRequestHandler *TransferFactory::createResource(Core::Configuration &configuration, Core::MetricService &metricService) {
        return new TransferHandler(configuration, metricService);
    }
}

