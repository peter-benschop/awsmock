//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_LIST_FUNCTION_REQUEST_H
#define AWSMOCK_DTO_LAMBDA_LIST_FUNCTION_REQUEST_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/dto/lambda/model/Environment.h>
#include <awsmock/dto/lambda/model/Function.h>
#include <awsmock/entity/lambda/Lambda.h>

namespace AwsMock::Dto::Lambda {

    struct ListFunctionResponse {

        /**
         * List of queues
         */
        Database::Entity::Lambda::LambdaList lambdaList;

        /**
         * Name of the function
         */
        FunctionList functions;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson();

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString();

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, ListFunctionResponse &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_LIST_FUNCTION_REQUEST_H
