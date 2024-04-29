//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_MESSAGE_H
#define AWSMOCK_DB_ENTITY_SQS_MESSAGE_H

// C++ includes
#include <algorithm>
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/Parser.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/NumberUtils.h>
#include <awsmock/entity/sqs/MessageAttribute.h>
#include <awsmock/entity/sqs/MessageStatus.h>
#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database::Entity::SQS {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * SQS message entity
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
        Poco::DateTime reset;

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
         * List of sqs
         */
        MessageAttributeList attributes;

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
         * @param m message
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Message &m);
    };

    typedef struct Message Message;
    typedef std::vector<Message> MessageList;

}// namespace AwsMock::Database::Entity::SQS

#endif// AWSMOCK_DB_ENTITY_SQS_MESSAGE_H
