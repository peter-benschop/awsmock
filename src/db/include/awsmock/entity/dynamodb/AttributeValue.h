//
// Created by vogje01 on 12/21/23.
//

#ifndef AWSMOCK_ENTITY_DYNAMODB_ATTRIBUTE_VALUE_H
#define AWSMOCK_ENTITY_DYNAMODB_ATTRIBUTE_VALUE_H

// C++ includes
#include <string>
#include <map>

// Poco includes
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock include
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Database::Entity::DynamoDb {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;
  using bsoncxx::to_json;

  struct AttributeValue {

    /**
     * String value
     */
    std::string stringValue;

    /**
     * String set value
     */
    std::vector<std::string> stringSetValue;

    /**
     * Number value
     */
    std::string numberValue;

    /**
     * Number set value
     */
    std::vector<std::string> numberSetValue;

    /**
     * Boolean value
     */
    bool boolValue;

    /**
     * Null value
     */
    bool nullValue;

    /**
     * Creation date
     */
    Poco::DateTime created = Poco::DateTime();

    /**
     * Last modification date
     */
    Poco::DateTime modified = Poco::DateTime();

    /**
     * Convert to JSON value
     *
     * @return JSON object
     */
    [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

    /**
     * Convert from JSON object.
     *
     * @param jsonObject JSON object
     */
    void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

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
    friend std::ostream &operator<<(std::ostream &os, const AttributeValue &r);

  };
} // namespace AwsMock::Dto::DynampDb

#endif // AWSMOCK_ENTITY_DYNAMODB_ATTRIBUTE_VALUE_H
