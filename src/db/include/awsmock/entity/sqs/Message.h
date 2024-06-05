//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_MESSAGE_H
#define AWSMOCK_DB_ENTITY_SQS_MESSAGE_H

// C++ includes
#include <algorithm>
#include <chrono>
#include <string>
#include <vector>

// Poco includes
#include <Poco/JSON/Parser.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core//DateTimeUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/NumberUtils.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/entity/sqs/MessageAttribute.h>
#include <awsmock/entity/sqs/MessageStatus.h>

namespace AwsMock::Database::Entity::SQS {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;
    using std::chrono::system_clock;

    /**
     * @brief SQS message entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Message {

        /**
         * ID
         */
        std::string oid;

        /**
         * Aws region name
         */
        std::string region;

        /**
         * Queue URL
         */
        std::string queueUrl;

        /**
         * Queue name
         */
        std::string queueName;

        /**
         * Message body
         */
        std::string body;

        /**
         * Status
         */
        MessageStatus status = MessageStatus::INITIAL;

        /**
         * Last send datetime
         */
        system_clock::time_point reset;

        /**
         * Send retries
         */
        int retries = 0;

        /**
         * Message ID
         */
        std::string messageId;

        /**
         * Receipt handle
         */
        std::string receiptHandle;

        /**
         * MD5 sum body
         */
        std::string md5Body;

        /**
         * MD5 sum sqs user attributes
         */
        std::string md5UserAttr;

        /**
         * MD5 sum sqs system attributes
         */
        std::string md5SystemAttr;

        /**
         * Attributes
         *
         * Fixed system attributes:
         *
         * - ApproximateReceiveCount
         * - ApproximateFirstReceiveTimestamp
         * - MessageDeduplicationId
         * - MessageGroupId
         * - SenderId
         * - SentTimestamp
         * - SequenceNumber
         * - SequenceNumber
         */
        std::map<std::string, std::string> attributes;

        /**
         * List of message attributes.
         *
         * This are the user contributed message attributes.
         */
        MessageAttributeList messageAttributes;

        /**
         * Creation date
         */
        system_clock::time_point created = std::chrono::system_clock::now();

        /**
         * Last modification date
         */
        system_clock::time_point modified = std::chrono::system_clock::now();

        /**
         * @brief Checks for the existence of a attribute with the given key.
         *
         * @param key attribute key
         * @return true if attribute with the given key exists
         */
        bool HasAttribute(const std::string &key);

        /**
         * @brief Returns the given attribute as integer
         *
         * @param key attribute key
         * @return true if attribute with the given key exists
         */
        int GetIntAttribute(const std::string &key);

        /**
         * @brief Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document.
         */
        void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * @brief Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * @brief Converts the entity to a JSON object
         *
         * @param jsonObject JSON object
         */
        void FromJsonObject(Poco::JSON::Object::Ptr jsonObject);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @param os output stream
         * @param m message
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Message &m);
    };

    typedef struct Message Message;
    typedef std::vector<Message> MessageList;

}// namespace AwsMock::Database::Entity::SQS

#endif// AWSMOCK_DB_ENTITY_SQS_MESSAGE_H
