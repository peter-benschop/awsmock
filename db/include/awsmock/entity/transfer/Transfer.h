//
// Created by vogje01 on 07/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_TRANSFER_H
#define AWSMOCK_DB_ENTITY_TRANSFER_H

// C++ includes
#include <string>
#include <vector>
#include <iostream>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

namespace AwsMock::Database::Entity::Transfer {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::view_or_value;
    using bsoncxx::document::view;
    using bsoncxx::document::value;

    struct Transfer {

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
       * ARN
       */
      std::string arn;

      /**
       * Last transfer server start
       */
      Poco::DateTime lastStarted;

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
      [[nodiscard]] view_or_value<view, value> ToDocument() const {

          view_or_value<view, value> transferDoc = make_document(
              kvp("region", region),
              kvp("name", name),
              kvp("arn", arn),
              kvp("lastStarted", bsoncxx::types::b_date(std::chrono::milliseconds(lastStarted.timestamp().epochMicroseconds() / 1000))),
              kvp("created", bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
              kvp("modified", bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

          return transferDoc;
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          name = mResult.value()["name"].get_string().value.to_string();
          arn = mResult.value()["arn"].get_string().value.to_string();
          lastStarted = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value) / 1000));
          created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
          modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          name = mResult.value()["name"].get_string().value.to_string();
          arn = mResult.value()["arn"].get_string().value.to_string();
          lastStarted = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["lastStarted"].get_date().value) / 1000));
          created = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
          modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));
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
      friend std::ostream &operator<<(std::ostream &os, const Transfer &m) {
          os << "Transfer={oid='" << m.oid << "' region='" << m.region << "' name='" << m.name << "' arn='" << m.arn <<
             "' lastStarted='" << Poco::DateTimeFormatter().format(m.lastStarted, Poco::DateTimeFormat::HTTP_FORMAT) <<
             "' created='" << Poco::DateTimeFormatter().format(m.created, Poco::DateTimeFormat::HTTP_FORMAT) <<
             "' modified='" << Poco::DateTimeFormatter().format(m.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
          return os;
      }

    };

    typedef struct Transfer Transfer;
    typedef std::vector<Transfer> TransferList;
}
#endif //AWSMOCK_DB_ENTITY_TRANSFER_H
