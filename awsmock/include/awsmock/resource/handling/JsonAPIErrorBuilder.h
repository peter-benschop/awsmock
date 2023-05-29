//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOUCE_HANDLING_JSONAPIERRORBUILDER_H
#define AWSMOCK_RESOUCE_HANDLING_JSONAPIERRORBUILDER_H

// C++ standard includes
#include <utility>

// Libri includes
#include "awsmock/resource/handling/IResourceBuilder.h"
#include "awsmock/resource/handling/IJsonAPIErrorBuilder.h"

namespace AwsMock {

    class JsonAPIErrorBuilder : public IJsonAPIErrorBuilder {
    public:
        explicit JsonAPIErrorBuilder(std::string );

        ~JsonAPIErrorBuilder() override = default;

        //
        Poco::DynamicStruct &build() override;

        void withStatusCode(int) override;

        void withType(const std::string &) override;

        void sourceAt(const std::string &) override;

        void withDetails(const std::string &) override;

    private:
        std::string host;
        Poco::DynamicStruct commonError;
        Poco::DynamicStruct rootJsonStructure;
        Poco::Dynamic::Array errorsCollection;
        Poco::DynamicStruct sourceErrorPointer;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOUCE_HANDLING_JSONAPIERRORBUILDER_H
