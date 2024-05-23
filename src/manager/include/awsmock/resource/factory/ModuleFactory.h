//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_FACTORY_MODULEFACTORY_H
#define AWSMOCK_RESOURCE_FACTORY_MODULEFACTORY_H

// AwsMock includes
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/resource/factory/IFactory.h>
#include <awsmock/resource/handler/ModuleHandler.h>

namespace AwsMock::Manager {

    /**
     * Module factory
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class ModuleFactory : public IFactory {

      public:

        /**
         * Create a new resource handler.
         *
         * @param serverMap server map
         * @return resource handler
         */
        Poco::Net::HTTPRequestHandler *createResource(Service::ServerMap &serverMap) override;
    };

}// namespace AwsMock::Manager

#endif// AWSMOCK_RESOURCE_FACTORY_MODULEFACTORY_H
