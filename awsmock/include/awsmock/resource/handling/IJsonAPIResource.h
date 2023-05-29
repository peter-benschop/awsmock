//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCE_H
#define AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCE_H

#include <string>
#include "Poco/DynamicStruct.h"

namespace AwsMock {

    /**
     * It builds a Json API main resource.
     *
     * @see http://jsonapi.org
     */
    class IJsonAPIResource
    {
    public:
        virtual void hostedAt(const std::string &) = 0;
        virtual void withType(const std::string &) = 0;
        virtual void withIdentity(const std::string &) = 0;

        virtual void linkTo(const std::string &, const std::string &) = 0;
        virtual void linkTo(const std::string &, const Poco::DynamicStruct &) = 0;

        virtual void addAttribute(const std::string &, const std::string &) = 0;
        virtual void addAttribute(const std::string &, const Poco::DynamicAny &) = 0;

        virtual void withMetadata(const std::string &, const std::string &) = 0;
        virtual void withMetadata(const std::string &, const Poco::DynamicStruct &) = 0;
        virtual void withMetadata(const std::string &, const Poco::Dynamic::Array &) = 0;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_IJSONAPIRESOURCE_H
