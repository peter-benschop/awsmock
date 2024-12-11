//
// Created by vogje01 on 4/30/24.
//

#ifndef AWSMOCK_DTO_LAMBDA_ERROR_H
#define AWSMOCK_DTO_LAMBDA_ERROR_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::Lambda {

    struct Error {

        /**
         * Error code
         */
        std::string errorCode;

        /**
         * Error message
         */
        std::string message;

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Error &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif//AWSMOCK_DTO_LAMBDA_ERROR_H
