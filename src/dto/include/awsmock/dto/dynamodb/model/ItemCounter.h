//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_DYNAMODB_ITEM_COUNTER_H
#define AWSMOCK_DTO_DYNAMODB_ITEM_COUNTER_H

// C++ includes
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/dynamodb/model/AttributeValue.h>
#include <awsmock/entity/dynamodb/Item.h>

namespace AwsMock::Dto::DynamoDb {

    struct ItemCounter {

        /**
         * Table name
         */
        std::string tableName;

        /**
         * Item ID
         */
        std::string id;

        /**
         * Item size in bytes
         */
        long size = 0;

        /**
         * Attributes
         */
        Database::Entity::DynamoDb::Item item;

        /**
         * Create timestamp
         */
        system_clock::time_point created;

        /**
         * Create timestamp
         */
        system_clock::time_point modified;

        /**
         * @brief Convert to a BSON document
         *
         * @return BSON document
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const ItemCounter &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_ITEM_COUNTER_H
