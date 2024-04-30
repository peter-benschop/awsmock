//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SNS_SUBSCRIPTION_H
#define AWSMOCK_DB_ENTITY_SNS_SUBSCRIPTION_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Database::Entity::SNS {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * SNS message attribute entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Subscription {

        /**
         * Protocol
         */
        std::string protocol;

        /**
         * Endpoint
         */
        std::string endpoint;

        /**
         * Subscription ARN
         */
        std::string subscriptionArn;

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
        [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view_or_value> mResult);

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
         * @param os output stream
         * @param m subscription entity
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Subscription &m);
    };

    typedef std::vector<Subscription> SubscriptionList;

}// namespace AwsMock::Database::Entity::SNS
#endif// AWSMOCK_DB_ENTITY_SNS_SUBSCRIPTION_H
