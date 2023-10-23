//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/resource/factory/Factory.h"

namespace AwsMock::Resource::Factory {

    IFactory *Factory::createResourceFactory(std::string &index) {

        IFactory *factory = nullptr;
        if (index == "AwsMock::Resource::Factory::S3Factory") {
            factory = new S3Factory();
        } else if (index == "AwsMock::Resource::Factory::SQSFactory") {
            factory = new SQSFactory();
        } else if (index == "AwsMock::Resource::Factory::SNSFactory") {
            factory = new SNSFactory();
        } else if (index == "AwsMock::Resource::Factory::LambdaFactory") {
            factory = new LambdaFactory();
        } else if (index == "AwsMock::Resource::Factory::TransferFactory") {
            factory = new TransferFactory();
        } else if (index == "AwsMock::Resource::Factory::ModuleFactory") {
          factory = new ModuleFactory();
        }
        return factory;
    }
}
