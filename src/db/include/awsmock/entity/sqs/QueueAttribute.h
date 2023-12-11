//
// Created by vogje01 on 12/10/23.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_QUEUE_ATTRIBUTE_H
#define AWSMOCK_DB_ENTITY_SQS_QUEUE_ATTRIBUTE_H

// C++ includes
#include <string>
#include <vector>

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
#include <awsmock/entity/sqs/RedrivePolicy.h>

namespace AwsMock::Database::Entity::SQS {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

  struct QueueAttribute {

    /**
     * Delay seconds
     */
    int delaySeconds = 0;

    /**
     * Max message size (256kB)
     */
    int maxMessageSize = 262144;

    /**
     * Max retention period (4d)
     */
    int messageRetentionPeriod = 345600;

    /**
     * Receive message timeout
     */
    int receiveMessageWaitTime = 20;

    /**
     * Visibility timeout
     */
    int visibilityTimeout = 30;

    /**
     * Policy
     *
     * <p>The queue's policy. A valid AWS policy.</p>
     */
    std::string policy;

    /**
     * Redrive policy
     *
     * <p>JSON string</p>
     */
    RedrivePolicy redrivePolicy;

    /**
     * Redrive allow policy
     *
     * <p>JSON string</p>
     */
    std::string redriveAllowPolicy;

    /**
     * Number of message counter
     */
    long approximateNumberOfMessages = 0;

    /**
     * Delay counter
     */
    long approximateNumberOfMessagesDelayed = 0;

    /**
     * Not visible counter
     */
    long approximateNumberOfMessagesNotVisible = 0;

    /**
     * AWS ARN
     */
    std::string queueArn;

    /**
     * Converts the entity to a MongoDB document
     *
     * @return entity as MongoDB document.
     */
    [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

    /**
     * Converts the MongoDB document to an entity
     *
     * @param mResult MongoDB document view.
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
     * @return DTO as string for logging.
     */
    void FromJsonObject(const Poco::JSON::Object::Ptr& jsonObject);

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
     * @param r queue attribute
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const QueueAttribute &r);

  };

} // namespace AwsMock::Database::Entity::SQS

#endif // AWSMOCK_DB_ENTITY_SQS_QUEUE_ATTRIBUTE_H
