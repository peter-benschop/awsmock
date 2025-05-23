//
// Created by vogje01 on 5/22/24.
//

#ifndef AWSMOCK_DTO_DYNAMODB_KEY_H
#define AWSMOCK_DTO_DYNAMODB_KEY_H

// C++ includes
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/dynamodb/model/AttributeValue.h>
namespace AwsMock::Dto::DynamoDb {

    /**
     * @brief DynamoDB item key
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Key {

        /**
         * Name
         */
        std::map<std::string, AttributeValue> keys;

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
         * @param document JSON object
         */
        void FromDocument(const view_or_value<view, value> &document);

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
        friend std::ostream &operator<<(std::ostream &os, const Key &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif//AWSMOCK_DTO_DYNAMODB_KEY_H
