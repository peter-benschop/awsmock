//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_LAMBDA_TRIGGER_COUNTER_H
#define AWSMOCK_DTO_SQS_LAMBDA_TRIGGER_COUNTER_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SQS {

    struct LambdaTriggerCounter {

        /**
         * UUID
         */
        std::string uuid;

        /**
         * AWS resource ARN
         */
        std::string arn;

        /**
         * Enabled flag
         */
        bool enabled;

        /**
         * @brief Converts the DTO to a JSON string.
         *
         * @return DTO as JSON string.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const LambdaTriggerCounter &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_LAMBDA_TRIGGER_COUNTER_H
