//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCEBUILDER_H
#define AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCEBUILDER_H

#include "awsmock/resource/handling/IResourceBuilder.h"
#include "awsmock/resource/handling/IJsonAPIResource.h"

namespace AwsMock {

    class IJsonAPIResourceBuilder
            : public IResourceBuilder,
              public IJsonAPIResource {
    public:
        virtual ~IJsonAPIResourceBuilder() = default;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCEBUILDER_H
