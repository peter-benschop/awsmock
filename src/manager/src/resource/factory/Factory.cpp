//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/resource/factory/Factory.h"

namespace AwsMock::Resource::Factory {

  IFactory *Factory::createResourceFactory(std::string &index) {

    IFactory *factory = nullptr;
    if (index == "AwsMock::Resource::Factory::ModuleFactory") {
      factory = new ModuleFactory();
    }
    return factory;
  }
}
