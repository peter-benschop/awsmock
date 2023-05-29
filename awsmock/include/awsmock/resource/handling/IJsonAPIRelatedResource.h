//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_IJSONAPIRELATEDRESOURCE_H
#define AWSMOCK_RESOURCE_HANDLING_IJSONAPIRELATEDRESOURCE_H

// C++ standard includes
#include <string>

namespace AwsMock {

    /*!
     * It builds a Json API related resource.
     *
     * @see http://jsonapi.org
     */
    class IJsonAPIRelatedResource {
    public:

        /*!
         * Json API related resources have identifiers.
         * This is the built related resource identifier.
         *
         * @return The related resource identifier.
         */
        virtual std::string identifier() const = 0;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_IJSONAPIRELATEDRESOURCE_H
