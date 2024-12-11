//
// Created by vogje01 on 07/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_DYNAMODB_TABLE_H
#define AWSMOCK_DB_ENTITY_DYNAMODB_TABLE_H

// C++ includes
#include <chrono>
#include <map>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/DatabaseException.h>

namespace AwsMock::Database::Entity::DynamoDb {

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
        void FromDocument(std::optional<view> mResult);

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
