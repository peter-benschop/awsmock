//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/resource/factory/S3Factory.h"

namespace AwsMock::Resource::Factory {

    Poco::Net::HTTPRequestHandler *S3Factory::createResource(Core::Configuration &configuration, Core::MetricService &metricService) {
        auto resource = new S3Handler(configuration, metricService);
        resource->setApplicationService(
            Application::PollServiceFactory::createService()
        );
        return resource;
    }
}

