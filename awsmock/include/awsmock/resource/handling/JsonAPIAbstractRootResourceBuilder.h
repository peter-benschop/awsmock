//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_JSONAPIABSTRACTROOTRESOURCEBUILDER_H
#define AWSMOCK_RESOURCE_HANDLING_JSONAPIABSTRACTROOTRESOURCEBUILDER_H

#include "awsmock/resource/handling/JsonAPIAbstractResourceBuilder.h"
#include "awsmock/resource/handling/JsonAPIAbstractRelatedResourceBuilder.h"

namespace AwsMock {

    class IRelatedResourceBuilder;

    class IJsonAPIResourceBuilder;

    class JsonAPIAbstractRootResourceBuilder : public JsonAPIAbstractResourceBuilder {
    public:
        /**
         * Default Destructor
         */
        ~JsonAPIAbstractRootResourceBuilder() override = default;

        void addRelatedResource(IRelatedResourceBuilder *);

        void addIncludeResource(IJsonAPIResourceBuilder *);

        Poco::DynamicStruct &build() final;

    protected:
        explicit JsonAPIAbstractRootResourceBuilder(const std::string &);

    private:
        Poco::Dynamic::Array includes;
        Poco::DynamicStruct relationships;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_JSONAPIABSTRACTROOTRESOURCEBUILDER_H
