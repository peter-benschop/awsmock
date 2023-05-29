//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_JSONAPIRESOURCECOLLECTIONBUILDER_H
#define AWSMOCK_RESOURCE_HANDLING_JSONAPIRESOURCECOLLECTIONBUILDER_H

#include "awsmock/resource/handling/IJsonAPIResourceCollectionBuilder.h"

namespace AwsMock {

    class JsonAPIResourceCollectionBuilder : public IJsonAPIResourceCollectionBuilder {
    public:
        JsonAPIResourceCollectionBuilder();

        Poco::DynamicStruct &build() override;

        void hostedAt(const std::string &) override;

        void addResource(IJsonAPIResourceBuilder *) override;

        void withMetadata(const std::string &) override;

        void withMetadata(const Poco::DynamicStruct &) override;

        void withMetadata(const Poco::Dynamic::Array &) override;

        void linkTo(const std::string &, const std::string &) override;

        void linkTo(const std::string &, const Poco::DynamicStruct &) override;

    private:
        Poco::DynamicStruct links;
        std::string resourceRootURL;
        Poco::DynamicStruct metadata;
        Poco::DynamicStruct structRoot;
        Poco::DynamicStruct resourceBasic;
        Poco::Dynamic::Array dataArrayRoot;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_JSONAPIRESOURCECOLLECTIONBUILDER_H
