//
// Created by vogje01 on 03/09/2023.
//

#ifndef AWSMOCK_ENTITY_LAMBDA_EPHEMERALSTORAGE_H
#define AWSMOCK_ENTITY_LAMBDA_EPHEMERALSTORAGE_H

// C++ includes
#include <string>
#include <vector>
#include <sstream>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

namespace AwsMock::Database::Entity::Lambda {

    struct EphemeralStorage {

      /**
       * Temporary disk space in MB. Default: 512 MB, Range: 512 - 10240 MB
       */
      long size = 512;

      /**
       * Converts the MongoDB document to an entity
       *
       * @return entity.
       */
      [[maybe_unused]] void FromDocument(mongocxx::stdx::optional <bsoncxx::document::view> mResult);

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
      friend std::ostream &operator<<(std::ostream &os, const EphemeralStorage &m);

    };

} // namespace AwsMock::Database::Entity::Lambda

#endif // AWSMOCK_ENTITY_LAMBDA_EPHEMERALSTORAGE_H
