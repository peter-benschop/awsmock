//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/resource/factory/S3Factory.h"

namespace AwsMock::Resource::Factory {

    Poco::Net::HTTPRequestHandler *S3Factory::createResource(Core::Configuration &configuration, Core::MetricService &metricService) {
        return new S3Handler(configuration, metricService);
    }
}

