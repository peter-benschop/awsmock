//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_OBJECT_H
#define AWSMOCK_DB_ENTITY_S3_OBJECT_H

// C++ includes
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <map>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/exception/exception.hpp>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Database::Entity::S3 {

  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;
  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  /**
   * S3 object entity
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct Object {

    /**
     * ID
     */
    std::string oid;

    /**
     * Aws region name
     */
    std::string region;

    /**
     * Bucket name
     */
    std::string bucket;

    /**
     * Object key
     */
    std::string key;

    /**
     * Object owner
     */
    std::string owner;

    /**
     * Object size
     */
    long size;

    /**
     * Object MD5Sum
     */
    std::string md5sum;

    /**
     * Object sha1Sum
     */
    std::string sha1sum;

    /**
     * Object sha256Sum
     */
    std::string sha256sum;

    /**
     * Object content type
     */
    std::string contentType;

    /**
     * Metadata
     */
    std::map<std::string, std::string> metadata;

    /**
     * Object internal name
     */
    std::string internalName;

    /**
     * Object version ID
     */
    std::string versionId;

    /**
     * Creation date
     */
    Poco::DateTime created;

    /**
     * Last modification date
     */
    Poco::DateTime modified;

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
     * @return DTO as string for logging.
     */
    void FromJsonObject(Poco::JSON::Object::Ptr jsonObject);

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
     * @param object object entity
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Object &object);
  };

  typedef struct Object Object;
  typedef std::vector<Object> ObjectList;

}
// namespace AwsMock::Database::S3::Entity

#endif //AWSMOCK_DB_ENTITY_S3_OBJECT_H
