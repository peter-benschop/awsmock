//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_ATTRIBUTE_COUNTER_H
#define AWSMOCK_DTO_SQS_ATTRIBUTE_COUNTER_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SQS {

    struct AttributeCounter {

        /**
         * Key
         */
        std::string attributeKey;

        /**
         * Value
         */
        std::string attributeValue;

        /**
         * @brief Converts the DTO to a JSON string.
         *
         * @return DTO as JSON string.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

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
        friend std::ostream &operator<<(std::ostream &os, const AttributeCounter &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SQS_ATTRIBUTE_COUNTER_H
