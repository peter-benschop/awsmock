//
// Created by vogje01 on 10/2/24.
//

#ifndef AWSMOCK_DB_ENTITY_COUNTER_H
#define AWSMOCK_DB_ENTITY_COUNTER_H

// C++ includes
#include <sstream>
#include <string>
#include <vector>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Database::Entity::Monitoring {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;
    using std::chrono::system_clock;

    struct Counter {

        /**
         * Object ID
         */
        std::string oid;

        /**
         * Name
         */
        std::string name;

        /**
         * Label name
         */
        std::string labelName;

        /**
         * Label value
         */
        std::string labelValue;

        /**
         * Value
         */
        double performanceValue;

        /**
         * Timestamp
         */
        system_clock::time_point timestamp = system_clock::now();


        /**
         * @brief Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document view.
         */
        [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * @brief Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the DTO to a JSON object.
         *
         * @return DTO as JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
         * @param tag tag entity
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Counter &counter);
    };
};// namespace AwsMock::Database::Entity::Monitoring
#endif//AWSMOCK_DB_ENTITY_COUNTER_H
