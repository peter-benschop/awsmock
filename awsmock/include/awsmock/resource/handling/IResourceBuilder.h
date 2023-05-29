//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_IRESOURCEBUILDER_H
#define AWSMOCK_RESOURCE_HANDLING_IRESOURCEBUILDER_H

#include "Poco/DynamicStruct.h"

namespace AwsMock {

    class IResourceBuilder {
    public:
        virtual Poco::DynamicStruct &build() = 0;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_IRESOURCEBUILDER_H
