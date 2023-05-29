//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCECOLLECTIONBUILDER_H
#define AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCECOLLECTIONBUILDER_H

#include "awsmock/resource/handling/IResourceBuilder.h"
#include "awsmock/resource/handling/IJsonAPIResourceCollection.h"

namespace AwsMock {

    class IJsonAPIResourceCollectionBuilder
            : public IResourceBuilder,
              public IJsonAPIResourceCollection {
    public:
        virtual ~IJsonAPIResourceCollectionBuilder() = default;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCECOLLECTIONBUILDER_H
