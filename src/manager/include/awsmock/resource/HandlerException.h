//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_RESOURCE_HANDLEREXCEPTION_H
#define AWSMOCK_RESOURCE_HANDLEREXCEPTION_H

// C++ standard includes
#include <stdexcept>
#include <utility>

namespace AwsMock {

    class HandlerException : public std::exception {
      public:
        HandlerException(std::string type, std::string message, int statusCode);

        [[nodiscard]] int code() const;

        [[nodiscard]] std::string type() const;

        [[nodiscard]] std::string message() const;

      private:
        int _statusCode;
        std::string _type;
        std::string _message;
    };
}// namespace AwsMock

#endif// AWSMOCK_RESOURCE_HANDLEREXCEPTION_H
