//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_FACTORY_H
#define AWSMOCK_RESOURCE_FACTORY_H

// C++ standard includes
#include <string>

// AwsMOck includes
#include "awsmock/resource/factory/S3Factory.h"
#include "awsmock/resource/factory/SQSFactory.h"
#include "awsmock/resource/factory/SNSFactory.h"
#include "awsmock/resource/factory/LambdaFactory.h"
#include "awsmock/resource/factory/TransferFactory.h"

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
