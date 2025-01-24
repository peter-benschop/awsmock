//
// Created by vogje01 on 12/21/23.
//

#ifndef AWSMOCK_DTO_DYNAMODB_ATTRIBUTE_VALUE_H
#define AWSMOCK_DTO_DYNAMODB_ATTRIBUTE_VALUE_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::DynamoDb {

    /**
     * DynamoDB attribute value
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct AttributeValue {

        /**
         * Type
         */
        std::string type;

        /**
         * Value
         */
        std::string attributeValue;

        /**
         * String value
         */
        std::string stringValue;

        /**
         * String set value
         */
        std::vector<std::string> stringSetValue;

        /**
         * Number value
         */
        std::string numberValue;

        /**
         * Number set value
         */
        std::vector<std::string> numberSetValue;

        /**
         * Boolean value
         */
        std::shared_ptr<bool> boolValue;

        /**
         * Null value
         */
        std::shared_ptr<bool> nullValue;

        /**
         * @brief Convert to JSON value
         *
         * @return JSON object
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert to JSON value
         *
         * @return JSON object
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Convert from JSON object.
         *
         * @param jsonObject JSON object
         */
        void FromDocument(const view &jsonObject);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const AttributeValue &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_ATTRIBUTE_VALUE_H
