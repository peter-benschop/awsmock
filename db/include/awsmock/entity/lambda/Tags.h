//
// Created by vogje01 on 03/09/2023.
//

#ifndef AWSMOCK_DB_ENTITY_LAMBDA_TAGS_H
#define AWSMOCK_DB_ENTITY_LAMBDA_TAGS_H

// C++ includes
#include <string>
#include <vector>
#include <sstream>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

namespace AwsMock::Database::Entity::Lambda {

    struct Tags {

      /**
       * Variables
       */
      std::vector<std::pair<std::string, std::string>> tags;

      /**
       * Checks whether a tags with the given tags key exists.
       *
       * @param key key of the tags
       * @return true if tags with the given key exists.
       */
      bool HasTag(const std::string &key);

      /**
       * Returns a given tags value by key
       *
       * @param eventName name of the event
       * @return found notification or notifications.end().
       */
      std::string GetTagValue(const std::string &key);

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
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
      friend std::ostream &operator<<(std::ostream &os, const Tags &t);

    };

} // namespace AwsMock::Database::Entity::Lambda

#endif // AWSMOCK_DB_ENTITY_LAMBDA_TAGS_H
