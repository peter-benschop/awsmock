//
// Created by vogje01 on 10/22/23.
//

#ifndef AWSMOCK_DB_ENTITY_SERVICE_SERVICE_H
#define AWSMOCK_DB_ENTITY_SERVICE_SERVICE_H

// C++ includes
#include <string>
#include <sstream>

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
#include <mongocxx/exception/exception.hpp>

// AwsMock includes
#include <awsmock/entity/service/ServiceStatus.h>

namespace AwsMock::Database::Entity::Service {

  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;
  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  struct Service {

    /**
     * ID
     */
    std::string oid;

    /**
     * Name
     */
    std::string name;

    /**
     * Status
     */
    ServiceStatus status;

    /**
     * Creation date
     */
    Poco::DateTime created = Poco::DateTime();

    /**
     * Last modification date
     */
    Poco::DateTime modified = Poco::DateTime();;

    /**
     * Converts the entity to a MongoDB document
     *
     * @return entity as MongoDB document.
     */
    [[nodiscard]] view_or_value<view, value> ToDocument() const;

    /**
     * Converts the MongoDB document to an entity
     *
     * @return entity.
     */
    void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult);

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
    friend std::ostream &operator<<(std::ostream &os, const Service &o);

  };

} // AwsMock::Database::Entity::Service

#endif // AWSMOCK_DB_ENTITY_SERVICE_SERVICE_H
