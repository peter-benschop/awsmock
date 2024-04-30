//
// Created by vogje01 on 06/09/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_LAMBDA_NOTIFICATION_H
#define AWSMOCK_DB_ENTITY_S3_LAMBDA_NOTIFICATION_H

// C++ includes
#include <chrono>
#include <sstream>
#include <string>

// Poco includes
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/entity/s3/FilterRule.h>

namespace AwsMock::Database::Entity::S3 {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * S3 bucket lambda notification entity.
     *
     * <p>
     * This is a child object of the bucket entity.
     * </p>
     *
     * @see AwsMock::Database::Entity::Bucket
     * @author jens.vogt\@opitz-consulting.com
     */
    struct LambdaNotification {

        /**
         * ID
         */
        std::string id;

        /**
         * Event
         */
        std::vector<std::string> events;

        /**
         * Lambda ARN
         */
        std::string lambdaArn;

        /**
         * Filter rules
         */
        std::vector<FilterRule> filterRules;

        /**
         * Check filter
         *
         * @param key object key
         * @return true in case filter exists and key matches
         */
        bool CheckFilter(const std::string &key);

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document.
         */
        LambdaNotification FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
        friend std::ostream &operator<<(std::ostream &os, const LambdaNotification &q);
    };

}// namespace AwsMock::Database::Entity::S3

#endif// AWSMOCK_DB_ENTITY_S3_LAMBDA_NOTIFICATION_H
