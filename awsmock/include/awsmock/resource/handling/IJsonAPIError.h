//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLING_IJSONAPIERROR_H
#define AWSMOCK_RESOURCE_HANDLING_IJSONAPIERROR_H

#include <string>

namespace AwsMock {

    /**
     * It builds a error in the Json API error format.
     *
     * @see http://jsonapi.org
     */
    class IJsonAPIError {
    public:

        virtual void withStatusCode(int) = 0;

        virtual void withType(const std::string &) = 0;

        virtual void withDetails(const std::string &) = 0;

        /**
         * Adds a pointer to the source of the error.
         *
         * @param pointer A URL to the source of the error.
         */
        virtual void sourceAt(const std::string &) = 0;
    };
} // namespace AwsMock

#endif // AWSMOCK_RESOURCE_HANDLING_IJSONAPIERROR_H
