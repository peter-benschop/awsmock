//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_JSONAPIABSTRACTRESOURCEBUILDER_H
#define AWSMOCK_RESOURCE_HANDLING_JSONAPIABSTRACTRESOURCEBUILDER_H

#include "awsmock/resource/handling/IJsonAPIResourceBuilder.h"

namespace AwsMock {

    /*!
     * It just make available Json API Resource Builder functions implementations
     * to other classes.
     *
     * @see IJsonAPIResourceBuilder
     */
    class JsonAPIAbstractResourceBuilder : public IJsonAPIResourceBuilder {
    public:
        // Default Destructor
        ~JsonAPIAbstractResourceBuilder() override = default;

        Poco::DynamicStruct &build() override;

        void hostedAt(const std::string &) override;

        void withType(const std::string &) override;

        void withIdentity(const std::string &) override;

        void linkTo(const std::string &, const std::string &) override;

        void linkTo(const std::string &, const Poco::DynamicStruct &) override;

        void addAttribute(const std::string &, const std::string &) override;

        void addAttribute(const std::string &, const Poco::DynamicAny &) override;

        void withMetadata(const std::string &, const std::string &) override;

        void withMetadata(const std::string &, const Poco::DynamicStruct &) override;

        void withMetadata(const std::string &, const Poco::Dynamic::Array &) override;

    protected:
        explicit JsonAPIAbstractResourceBuilder(const std::string &);

        Poco::DynamicStruct &structRootObject();

        Poco::Dynamic::Array &arrayRootObject();

    private:
        Poco::DynamicStruct links;
        std::string resourceRootURL;
        Poco::DynamicStruct metadata;
        Poco::DynamicStruct attributes;
        Poco::DynamicStruct structRoot;
        Poco::DynamicStruct resourceBasic;
        Poco::Dynamic::Array dataArrayRoot;

    };
} // namespace AwsMock
#endif // AWSMOCK_RESOURCE_HANDLING_JSONAPIABSTRACTRESOURCEBUILDER_H
