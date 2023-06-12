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
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/ServiceException.h>

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
       * Creation date
       */
      Poco::DateTime created = Poco::DateTime();

      /**
       * Last modification date
       */
      Poco::DateTime modified = Poco::DateTime();

      /**
       * Converts the entity to a MongoDB document
       *
       * @return entity as MongoDB document.
       */
      [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const {

          view_or_value<view, value> queueDoc = make_document(
              kvp("region", region),
              kvp("topicName", topicName),
              kvp("owner", owner),
              kvp("topicUrl", topicUrl),
              kvp("topicArn", topicArn),
              kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds()/1000))),
              kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds()/1000))));

          return queueDoc;
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          topicName = mResult.value()["topicName"].get_string().value.to_string();
          owner = mResult.value()["owner"].get_string().value.to_string();
          topicUrl = mResult.value()["topicUrl"].get_string().value.to_string();
          topicArn = mResult.value()["topicArn"].get_string().value.to_string();
          created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000000));
          modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000000));
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          topicName = mResult.value()["topicName"].get_string().value.to_string();
          owner = mResult.value()["owner"].get_string().value.to_string();
          topicUrl = mResult.value()["topicUrl"].get_string().value.to_string();
          topicArn = mResult.value()["topicArn"].get_string().value.to_string();
          created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000000));
          modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000000));
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

} // namespace AwsMock::Database::Entity::S3
#endif // AWSMOCK_DB_ENTITY_SQS_QUEUE_H
