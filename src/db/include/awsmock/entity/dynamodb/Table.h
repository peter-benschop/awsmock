//
// Created by vogje01 on 07/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_DYNAMODB_TABLE_H
#define AWSMOCK_DB_ENTITY_DYNAMODB_TABLE_H

// C++ includes
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/Object.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Database::Entity::DynamoDb {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;
  using bsoncxx::to_json;

  /**
   * DynamoDB table entity
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct Table {

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
     * Attributes
     */
    std::map<std::string, std::string> attributes;

    /**
     * Tags
     */
    std::map<std::string, std::string> tags;

    /**
     * Key schemas
     */
    std::map<std::string, std::string> keySchemas;

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
     * Converts the entity to a JSON string
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToJson() const;

    /**
     * Converts an JSON object to an entity
     *
     * @param jsonObject JSON object.
     */
    void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

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
     * @param d DynamoDB  entity
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Table &d);
  };

  typedef std::vector<Table> TableList;

} // namespace AwsMock::Database::Entity::DynamoDb

#endif // AWSMOCK_DB_ENTITY_DYNAMODB_TABLE_H
