//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SECRETSMANAGER_MESSAGE_H
#define AWSMOCK_DB_ENTITY_SECRETSMANAGER_MESSAGE_H

// C++ includes
#include <string>
#include <vector>
#include <algorithm>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/Parser.h>
#include <Poco/UUIDGenerator.h>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/NumberUtils.h>
#include <awsmock/entity/sqs/MessageAttribute.h>
#include <awsmock/entity/sqs/MessageStatus.h>

namespace AwsMock::Database::Entity::SecretsManager {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

  /**
   * SecretManager secrets entity.
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct Secret {

    /**
     * ID
     */
    std::string oid;

    /**
     * Aws region name
     */
    std::string region;

    /**
     * Secret name
     */
    std::string name;

    /**
     * Arn
     */
    std::string arn;

    /**
     * Secret ID
     */
    std::string secretId;

    /**
     * Version Id
     */
    std::string versionId;

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
     * @param os output stream
     * @param m message
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Secret &m);

  };

} // namespace AwsMock::Database::Entity::S3

#endif // AWSMOCK_DB_ENTITY_SECRETSMANAGER_MESSAGE_H
