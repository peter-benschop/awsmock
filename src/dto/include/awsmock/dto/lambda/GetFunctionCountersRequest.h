//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_GET_FUNCTION_COUNTERS_REQUEST_H
#define AWSMOCK_DTO_LAMBDA_GET_FUNCTION_COUNTERS_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/dto/lambda/model/Environment.h>
#include <awsmock/dto/lambda/model/EphemeralStorage.h>

namespace AwsMock::Dto::Lambda {

    struct GetFunctionCountersRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * function name
         */
        std::string functionName;

        /**
         * Convert from a JSON string.
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * Creates a JSON string from the object.
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
        friend std::ostream &operator<<(std::ostream &os, const GetFunctionCountersRequest &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_GET_FUNCTION_COUNTERS_REQUEST_H
