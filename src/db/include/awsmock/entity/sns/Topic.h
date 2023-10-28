//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SNS_TOPIC_H
#define AWSMOCK_DB_ENTITY_SNS_TOPIC_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/ServiceException.h>
#include <awsmock/entity/sns/Subscription.h>

namespace AwsMock::Database::Entity::SNS {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

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
     * Creation date
     */
    Poco::DateTime created = Poco::DateTime();

    /**
     * Last modification date
     */
    Poco::DateTime modified = Poco::DateTime();

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
    [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

    /**
     * Converts the MongoDB document to an entity
     *
     * @param mResult MongoDB document view.
     */
    [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult);

    /**
     * Converts the MongoDB document to an entity
     *
     * @param mResult MongoDB document view.
     */
    [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

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

  typedef struct Topic Topic;
  typedef std::vector<Topic> TopicList;

} // namespace AwsMock::Database::Entity::SNS
#endif // AWSMOCK_DB_ENTITY_SNS_TOPIC_H
