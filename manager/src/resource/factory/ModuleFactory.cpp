//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/resource/factory/ModuleFactory.h>

namespace AwsMock::Manager {

    Poco::Net::HTTPRequestHandler *ModuleFactory::createResource(Service::ServerMap &serverMap) {
        return new ModuleHandler(serverMap);
    }
}// namespace AwsMock::Manager
