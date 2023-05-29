//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_JSONAPIRESOURCEBUILDER_H
#define AWSMOCK_RESOURCE_HANDLING_JSONAPIRESOURCEBUILDER_H

#include "awsmock/resource/handling/JsonAPIAbstractRootResourceBuilder.h"

namespace AwsMock {

    class JsonAPIResourceBuilder : public JsonAPIAbstractRootResourceBuilder
    {
    public:
        JsonAPIResourceBuilder();
        explicit JsonAPIResourceBuilder(const std::string &);

        ~JsonAPIResourceBuilder() override;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_JSONAPIRESOURCEBUILDER_H
