//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_IJSONAPIERRORBUILDER_H
#define AWSMOCK_RESOURCE_HANDLING_IJSONAPIERRORBUILDER_H

#include "awsmock/resource/handling/IResourceBuilder.h"
#include "awsmock/resource/handling/IJsonAPIError.h"

namespace AwsMock {

    class IJsonAPIErrorBuilder :
            public IJsonAPIError,
            public IResourceBuilder {
    public:
        virtual ~IJsonAPIErrorBuilder() = default;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_IJSONAPIERRORBUILDER_H
