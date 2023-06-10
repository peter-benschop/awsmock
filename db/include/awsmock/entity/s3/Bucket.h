//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_BUCKET_H
#define AWSMOCK_DB_ENTITY_S3_BUCKET_H

// C++ includes
#include <string>
#include <chrono>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>

namespace AwsMock::Database::Entity::S3 {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::view_or_value;
    using bsoncxx::document::view;
    using bsoncxx::document::value;

    struct Bucket {

      /**
       * ID
       */
      std::string oid;

      /**
       * Bucket region
       */
      std::string region;

      /**
       * Bucket name
       */
      std::string name;

      /**
       * Bucket owner
       */
      std::string owner;

      /**
       * Creation date
       */
      std::chrono::time_point<std::chrono::system_clock> created = std::chrono::system_clock::now();

      /**
       * Last modification date
       */
      std::chrono::time_point<std::chrono::system_clock> modified = std::chrono::system_clock::now();

      /**
       * Converts the entity to a MongoDB document
       *
       * @return entity as MongoDB document.
       */
      [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const {

          view_or_value<view, value> bucketDoc = make_document(
              kvp("region", region),
              kvp("name", name),
              kvp("owner", owner),
              kvp("created", bsoncxx::types::b_date(created)),
              kvp("modified", bsoncxx::types::b_date(modified)));

          return bucketDoc;
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          name = mResult.value()["name"].get_string().value.to_string();
          owner = mResult.value()["owner"].get_string().value.to_string();
          created = bsoncxx::types::b_date(mResult.value()["created"].get_date());
          modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date());
      }

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

          oid = mResult.value()["_id"].get_oid().value.to_string();
          region = mResult.value()["region"].get_string().value.to_string();
          name = mResult.value()["name"].get_string().value.to_string();
          owner = mResult.value()["owner"].get_string().value.to_string();
          created = bsoncxx::types::b_date(mResult.value()["created"].get_date());
          modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date());
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
      friend std::ostream &operator<<(std::ostream &os, const Bucket &q) {
          os << "Bucket={oid='" + q.oid + "' region='" + q.region + "' name='" + q.name + "' owner='" + q.owner + " created='";
       //   os << std::put_time(std::localtime(reinterpret_cast<const time_t *>(&(q.created))), "%F %T.");
//          os << std::put_time(std::localtime(reinterpret_cast<const time_t *>(&(q.modified))), "%Y/%m/%d %I:%M:%S %p");
          os << "}";
          return os;
      }

    };

    typedef struct Bucket Bucket;
    typedef std::vector<Bucket> BucketList;

} // namespace AwsMock::Database::S3::Entity

#endif //AWSMOCK_DB_ENTITY_S3_BUCKET_H
