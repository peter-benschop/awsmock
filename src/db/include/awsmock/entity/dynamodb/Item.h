//
// Created by vogje01 on 07/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_DYNAMODB_ITEM_H
#define AWSMOCK_DB_ENTITY_DYNAMODB_ITEM_H

// C++ includes
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/stdx.hpp>

// Poco includes
#include <Poco/JSON/Object.h>

// AwsMock includes
#include <awsmock/entity/dynamodb/AttributeValue.h>
#include <awsmock/entity/dynamodb/Table.h>

namespace AwsMock::Database::Entity::DynamoDb {

    using bsoncxx::to_json;
    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;
    using std::chrono::system_clock;

    /**
     * @brief DynamoDB item entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Item {

        /**
         * ID
         */
        std::string oid;

        /**
         * AWS region name
         */
        std::string region;

        /**
         * Table name
         */
        std::string tableName;

        /**
         * Attributes
         */
        std::map<std::string, Entity::DynamoDb::AttributeValue> attributes;

        /**
         * Keys
         */
        std::map<std::string, Entity::DynamoDb::AttributeValue> keys;

        /**
         * Creation date
         */
        system_clock::time_point created = system_clock::now();

        /**
         * Last modification date
         */
        system_clock::time_point modified = system_clock::now();

        /**
         * @brief Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the MongoDB document to an entity
         *
         * @param mResult query result.
         */
        Entity::DynamoDb::Item FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * @brief Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Converts the entity to a JSON string
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @param os output stream
         * @param d DynamoDB  entity
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Item &d);
    };

    typedef std::vector<Item> ItemList;

}// namespace AwsMock::Database::Entity::DynamoDb

#endif// AWSMOCK_DB_ENTITY_DYNAMODB_ITEM_H
