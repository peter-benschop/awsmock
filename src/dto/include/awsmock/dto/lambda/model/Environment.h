//
// Created by vogje01 on 21/06/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_ENVIRONMENT_H
#define AWSMOCK_DTO_LAMBDA_ENVIRONMENT_H

// C++ standard includes
#include <string>

// AwsMock includes
#include "awsmock/core/exception/JsonException.h"
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/core/JsonUtils.h>
#include <awsmock/dto/lambda/model/Error.h>

namespace AwsMock::Dto::Lambda {

    struct EnvironmentVariables {

        /**
         * Environment variables
         */
        std::map<std::string, std::string> variables;

        /**
         * Error
         */
        Error error;

        /**
         * Convert to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Convert to a JSON string
         *
         * @param object JSON object
         */
        void FromJson(Poco::JSON::Object::Ptr object);

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const EnvironmentVariables &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif//AWSMOCK_DTO_LAMBDA_ENVIRONMENT_H
