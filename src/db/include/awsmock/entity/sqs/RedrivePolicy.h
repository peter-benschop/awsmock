//
// Created by vogje01 on 12/10/23.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_REDRIVE_POLICY_H
#define AWSMOCK_DB_ENTITY_SQS_REDRIVE_POLICY_H

// C++ includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/JSON/Parser.h>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Database::Entity::SQS {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

  /**
   * SQS queue re-drive policy entity
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct RedrivePolicy {

    /**
     * Dead letter queue target ARN
     */
    std::string deadLetterTargetArn;

    /**
     * Maximal number of retries, before the message will be send to the DQL
     */
    int maxReceiveCount = 0;

    /**
     * Parse values from a JSON stream
     *
     * @param body json input stream
     */
    void FromJson(const std::string &body);

    /**
     * Converts the DTO to a JSON representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToJson() const;

    /**
     * Converts the entity to a MongoDB document
     *
     * @return entity as MongoDB document.
     */
    [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

    /**
     * Converts the MongoDB document to an entity
     *
     * @param mResult MongoDB document.
     */
    [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

    /**
     * Converts the entity to a JSON object
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

    /**
     * Converts the entity to a JSON object
     *
     * @param jsonObject JSON object
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
     * @param r redrive policy
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const RedrivePolicy &r);

  };

} // namespace AwsMock::Database::Entity::SQS

#endif // AWSMOCK_DB_ENTITY_SQS_REDRIVE_POLICY_H
