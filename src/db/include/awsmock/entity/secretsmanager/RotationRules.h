//
// Created by vogje01 on 4/8/24.
//

#ifndef AWSMOCK_DB_ENTITY_SECRETSMANAGER_ROTATION_RULES_H
#define AWSMOCK_DB_ENTITY_SECRETSMANAGER_ROTATION_RULES_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPResponse.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/stdx.hpp>

// AwsMoc includes
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Database::Entity::SecretsManager {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * Rotation rules
     *
     * Example:
     * @code{.json}
     * {
     *   "AutomaticallyAfterDays": number,
     *   "Duration": "string",
     *   "ScheduleExpression": "string"
     * }
     * @endcode
     */
    struct RotationRules {

        /**
         * Automatic rotation period
         */
        long automaticallyAfterDays;

        /**
         * Duration
         */
        std::string duration;

        /**
         * Duration
         */
        std::string scheduleExpression;

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document.
         */
        void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * Converts the entity to a string representation.
         *
         * @return entity as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Converts the entity to a string representation.
         *
         * @return entity as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const RotationRules &r);
    };

}// namespace AwsMock::Database::Entity::SecretsManager

#endif// AWSMOCK_ENTITY_SECRETSMANAGER_ROTATION_RULES_H
