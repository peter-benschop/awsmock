//
// Created by vogje01 on 12/21/23.
//

#ifndef AWSMOCK_ENTITY_DYNAMODB_ATTRIBUTE_VALUE_H
#define AWSMOCK_ENTITY_DYNAMODB_ATTRIBUTE_VALUE_H

// C++ includes
#include <chrono>
#include <string>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock include
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/DatabaseException.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/utils/MongoUtils.h>

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
     * @brief DynamoDB attribute value entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct AttributeValue {

        /**
         * Type
         */
        std::string type;

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
        bool boolValue = false;

        /**
         * Null value
         */
        bool nullValue = false;

        /**
         * Creation date
         */
        system_clock::time_point created = system_clock::now();

        /**
         * Last modification date
         */
        system_clock::time_point modified = system_clock::now();

        /**
         * @brief Convert to JSON value
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * @brief Convert from JSON object.
         *
         * @param jsonObject JSON object
         */
        void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

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
        void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const AttributeValue &r);
    };
}// namespace AwsMock::Database::Entity::DynamoDb

#endif// AWSMOCK_ENTITY_DYNAMODB_ATTRIBUTE_VALUE_H
