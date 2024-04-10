//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DB_ENTITY_COGNITO_USER_H
#define AWSMOCK_DB_ENTITY_COGNITO_USER_H

// C++ includes
#include <string>
#include <map>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/entity/cognito/UserStatus.h>
#include <awsmock/entity/cognito/UserAttribute.h>

namespace AwsMock::Database::Entity::Cognito {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;
  using bsoncxx::to_json;

  /**
   * Cognito user entity
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct User {

    /**
     * MongoDB POD
     */
    std::string oid;

    /**
     * Aws region
     */
    std::string region;

    /**
     * User pool ID
     */
    std::string userPoolId;

    /**
     * User name
     */
    std::string userName;

    /**
     * Enabled
     */
    bool enabled;

    /**
     * Attributes
     */
    UserAttributeList userAttributes;

    /**
     * Status
     */
    UserStatus userStatus;

    /**
     * Password
     */
    std::string password;

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
     * @param mResult query result.
     */
    void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

    /**
     * Converts the entity to a JSON object
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

    /**
     * Converts the entity to a JSON object
     *
     * @param jsonObject JSON object.
     */
    void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

    /**
     * Converts the entity to a string representation.
     *
     * @return entity as string for logging.
     */
    [[nodiscard]] std::string ToString() const;

    /**
     * Stream provider.
     *
     * @param os output stream
     * @param user user entity
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const User &user);

  };

  typedef std::vector<User> UserList;
}
#endif // AWSMOCK_DB_ENTITY_COGNITO_USER_H
