//
// Created by vogje01 on 07/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_DYNAMODB_TABLE_H
#define AWSMOCK_DB_ENTITY_DYNAMODB_TABLE_H

// C++ includes
#include <chrono>
#include <string>
#include <vector>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/DatabaseException.h>

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
     * DynamoDB table entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Table {

        /**
         * ID
         */
        std::string oid;

        /**
         * AWS region name
         */
        std::string region;

        /**
         * Name
         */
        std::string name;

        /**
         * Table status
         */
        std::string status;

        /**
         * Attributes
         */
        std::map<std::string, std::string> attributes;

        /**
         * Tags
         */
        std::map<std::string, std::string> tags;

        /**
         * Key schemas
         */
        std::map<std::string, std::string> keySchemas;

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
        void FromDocument(mongocxx::stdx::optional<view> mResult);

        /**
         * @brief Converts the entity to a JSON string
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
        friend std::ostream &operator<<(std::ostream &os, const Table &d);
    };

    typedef std::vector<Table> TableList;

}// namespace AwsMock::Database::Entity::DynamoDb

#endif// AWSMOCK_DB_ENTITY_DYNAMODB_TABLE_H
