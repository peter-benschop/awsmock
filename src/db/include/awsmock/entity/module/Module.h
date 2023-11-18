//
// Created by vogje01 on 10/22/23.
//

#ifndef AWSMOCK_DB_ENTITY_MODULE_MODULE_H
#define AWSMOCK_DB_ENTITY_MODULE_MODULE_H

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
#include <awsmock/entity/module/ModuleStatus.h>

namespace AwsMock::Database::Entity::Module {

  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;
  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  struct Module {

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
    ModuleStatus status;

    /**
     * Executable
     */
    std::string executable = {};

    /**
     * HTTP port
     */
    int port = -1;

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
    [[nodiscard]] view_or_value<view, value> ToDocument() const;

    /**
     * Converts the MongoDB document to an entity
     *
     * @param mResult MongoDB document.
     */
    void FromDocument(mongocxx::stdx::optional<bsoncxx::document::value> mResult);

    /**
     * Converts the MongoDB document to an entity
     *
     * @param mResult MongoDB document.
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
     * @param os output stream
     * @param module module entity
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Module &module);

  };

  typedef std::vector<Module> ModuleList;

} // AwsMock::Database::Entity::Service

#endif // AWSMOCK_DB_ENTITY_MODULE_MODULE_H
