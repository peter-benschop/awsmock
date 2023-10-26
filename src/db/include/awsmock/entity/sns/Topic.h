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
    bool HasSubscription(const Subscription &subscription) {
      return find_if(subscriptions.begin(), subscriptions.end(), [subscription](const Subscription &s) {
        return s.protocol == subscription.protocol && s.endpoint == subscription.endpoint;
      }) != subscriptions.end();
    }

    /**
     * Converts the entity to a MongoDB document
     *
     * @return entity as MongoDB document.
     */
    [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const {

      auto subscriptionDocs = bsoncxx::builder::basic::array{};
      for (const auto &subscription : subscriptions) {
        subscriptionDocs.append(subscription.ToDocument());
      }

      view_or_value<view, value> topicDoc = make_document(
          kvp("region", region),
          kvp("topicName", topicName),
          kvp("owner", owner),
          kvp("topicUrl", topicUrl),
          kvp("topicArn", topicArn),
          kvp("subscriptions", subscriptionDocs),
          kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
          kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

      return topicDoc;
    }

    /**
     * Converts the MongoDB document to an entity
     *
     * @param mResult MongoDB document view.
     */
    [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

      oid = mResult.value()["_id"].get_oid().value.to_string();
      region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
      topicName = bsoncxx::string::to_string(mResult.value()["topicName"].get_string().value);
      owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
      topicUrl = bsoncxx::string::to_string(mResult.value()["topicUrl"].get_string().value);
      topicArn = bsoncxx::string::to_string(mResult.value()["topicArn"].get_string().value);
      created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
      modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

      bsoncxx::array::view subscriptionsView{mResult.value()["subscriptions"].get_array().value};
      for (bsoncxx::array::element subscriptionElement : subscriptionsView) {
        Subscription subscription{
            .protocol=bsoncxx::string::to_string(subscriptionElement["protocol"].get_string().value),
            .endpoint=bsoncxx::string::to_string(subscriptionElement["endpoint"].get_string().value),
            .subscriptionArn=bsoncxx::string::to_string(subscriptionElement["subscriptionArn"].get_string().value)
        };
        subscriptions.push_back(subscription);
      }
    }

    /**
     * Converts the MongoDB document to an entity
     *
     * @param mResult MongoDB document view.
     */
    [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

      oid = mResult.value()["_id"].get_oid().value.to_string();
      region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
      topicName = bsoncxx::string::to_string(mResult.value()["topicName"].get_string().value);
      owner = bsoncxx::string::to_string(mResult.value()["owner"].get_string().value);
      topicUrl = bsoncxx::string::to_string(mResult.value()["topicUrl"].get_string().value);
      topicArn = bsoncxx::string::to_string(mResult.value()["topicArn"].get_string().value);
      created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
      modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

      bsoncxx::array::view subscriptionsView{mResult.value()["subscriptions"].get_array().value};
      for (bsoncxx::array::element subscriptionElement : subscriptionsView) {
        Subscription subscription{
            .protocol=bsoncxx::string::to_string(subscriptionElement["protocol"].get_string().value),
            .endpoint=bsoncxx::string::to_string(subscriptionElement["endpoint"].get_string().value),
            .subscriptionArn=bsoncxx::string::to_string(subscriptionElement["subscriptionArn"].get_string().value)
        };
        subscriptions.push_back(subscription);
      }
    }

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToString() const {
      std::stringstream ss;
      ss << (*this);
      return ss.str();
    }

    /**
     * Stream provider.
     *
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Topic &q) {
      os << "Topic={id='" << q.oid << "' region='" << q.region << "' name='" << q.topicName << "' owner='" << q.owner << "' topicUrl='" << q.topicUrl <<
         "' topicArn='" << q.topicArn << "' created='" << Poco::DateTimeFormatter().format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) <<
         "' modified='" << Poco::DateTimeFormatter().format(q.created, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
      return os;
    }

  };

  typedef struct Topic Topic;
  typedef std::vector<Topic> TopicList;

} // namespace AwsMock::Database::Entity::SNS
#endif // AWSMOCK_DB_ENTITY_SNS_TOPIC_H
