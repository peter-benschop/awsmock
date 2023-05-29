//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCECOLLECTION_H
#define AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCECOLLECTION_H

// C++ standard includes
#include <string>

// Poco includes
#include "Poco/DynamicStruct.h"

// Libri includes
#include "awsmock/resource/handling/IJsonAPIResourceBuilder.h"

namespace AwsMock {

    /**
     * It builds a Json API resource collection.
     *
     * @see http://jsonapi.org
     */
    class IJsonAPIResourceCollection
    {
    public:
        virtual void hostedAt(const std::string & host) = 0;
        virtual void addResource(IJsonAPIResourceBuilder * resourceBuilder) = 0;

        virtual void withMetadata(const std::string &) = 0;
        virtual void withMetadata(const Poco::DynamicStruct &) = 0;
        virtual void withMetadata(const Poco::Dynamic::Array &) = 0;

        virtual void linkTo(const std::string &, const std::string &) = 0;
        virtual void linkTo(const std::string &, const Poco::DynamicStruct &) = 0;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCECOLLECTION_H
