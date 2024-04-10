//
// Created by vogje01 on 07/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_USER_H
#define AWSMOCK_DB_ENTITY_USER_H

// C++ includes
#include <string>
#include <vector>
#include <iostream>

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

namespace AwsMock::Database::Entity::Transfer {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

  /**
   * Transfer manager user entity
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct User {

    /**
     * User name
     */
    std::string userName;

    /**
     * Password
     */
    std::string password;

    /**
     * Home directory
     */
    std::string homeDirectory;

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
    [[maybe_unused]] void FromDocument(bsoncxx::document::view mResult);

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
     * @param m user
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const User &m);

  };

}
#endif // AWSMOCK_DB_ENTITY_USER_H
