//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLEREXCEPTION_H
#define AWSMOCK_RESOURCE_HANDLEREXCEPTION_H

// C++ standard includes
#include <stdexcept>
#include <utility>

namespace AwsMock {

    /**
     * Handler exception
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class HandlerException : public std::exception {

      public:

        /**
         * Handler exception
         *
         * @param type exception type
         * @param message exception message
         * @param statusCode HTTP status code
         */
        HandlerException(std::string type, std::string message, int statusCode);

        /**
         * Status code
         *
         * @return code
         */
        [[nodiscard]] int code() const;

        /**
         * Type
         *
         * @return type
         */
        [[nodiscard]] std::string type() const;

        /**
         * Status message
         *
         * @return message
         */
        [[nodiscard]] std::string message() const;

      private:

        /**
         * HTTP status code
         */
        int _statusCode;

        /**
         * Exception type
         */
        std::string _type;

        /**
         * Exception message
         */
        std::string _message;
    };

}// namespace AwsMock

#endif// AWSMOCK_RESOURCE_HANDLEREXCEPTION_H
