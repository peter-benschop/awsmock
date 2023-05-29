//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_JSONAPI_IRELATEDRESOURCEBUILDER_H
#define AWSMOCK_RESOURCE_HANDLING_JSONAPI_IRELATEDRESOURCEBUILDER_H

#include "awsmock/resource/handling/IResourceBuilder.h"
#include "awsmock/resource/handling/IJsonAPIRelatedResource.h"

namespace AwsMock {

    class IRelatedResourceBuilder :
            public IJsonAPIRelatedResource,
            public IResourceBuilder {
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_JSONAPI_IRELATEDRESOURCEBUILDER_H
