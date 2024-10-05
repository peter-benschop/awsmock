//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SNS_TOPIC_H
#define AWSMOCK_DB_ENTITY_SNS_TOPIC_H

// C++ includes
#include <chrono>
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
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/entity/sns/Subscription.h>
#include <awsmock/entity/sns/TopicAttribute.h>
#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database::Entity::SNS {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;
    using std::chrono::system_clock;

    /**
     * @brief SNS topic entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Topic {

        /**
         * ID
         */
        std::string oid;

        /**
         * AWS region
         */
        std::string region;

        /**
         * Topic name
         */
        std::string topicName;

        /**
         * Owner
         */
        std::string owner;

        /**
         * Topic URL
         */
        std::string topicUrl;

        /**
         * Topic ARN
         */
        std::string topicArn;

        /**
         * Subscriptions
         */
        SubscriptionList subscriptions;

        /**
         * Attributes
         */
        TopicAttribute topicAttribute;

        /**
         * Topic tags
         */
        std::map<std::string, std::string> tags;

        /**
         * Creation date
         */
        system_clock::time_point created = system_clock::now();

        /**
         * Last modification date
         */
        system_clock::time_point modified;

        /**
         * Checks whether a subscription with the given protocol/endpoint exists already.
         *
         * @param subscription name of the event
         * @return true if notification with the given event name exists.
         */
        bool HasSubscription(const Subscription &subscription);

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document view.
         */
        void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Converts the jsonObject to a entity
         *
         * @param jsonObject JSON object
         */
        void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

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
        friend std::ostream &operator<<(std::ostream &os, const Topic &q);
    };

    typedef std::vector<Topic> TopicList;

}// namespace AwsMock::Database::Entity::SNS

#endif// AWSMOCK_DB_ENTITY_SNS_TOPIC_H
