//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_FACTORY_H
#define AWSMOCK_RESOURCE_FACTORY_H

// C++ standard includes
#include <string>

// AwsMock includes
#include "awsmock/resource/factory/ModuleFactory.h"

namespace AwsMock::Resource::Factory {

    class IFactory;

    /**
     * HTTP resource factory
     */
    class Factory {
    public:

      /**
       * Creates a new resource factory.
       *
       * @param name resource factory name.
       * @return resource factory
       */
      static IFactory *createResourceFactory(std::string &name);

    private:
      /**
       * Default constructor
       */
      Factory() = default;;
    };
} // namespace AwsMock::RESOuRCE::factory

#endif // AWSMOCK_RESOURCE_FACTORY_H
