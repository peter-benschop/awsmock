//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_KMS_KEY_H
#define AWSMOCK_DB_ENTITY_KMS_KEY_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/DatabaseException.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database::Entity::KMS {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * KMS key entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Key {

        /**
         * ID
         */
        std::string oid;

        /**
         * AWS region
         */
        std::string region;

        /**
         * Key ID
         */
        std::string keyId;

        /**
         * Key usage
         */
        std::string keyUsage;

        /**
         * Key specification
         */
        std::string keySpec;

        /**
         * Key state
         */
        std::string keyState;

        /**
         * AWS ARN
         */
        std::string arn;

        /**
         * Description
         */
        std::string description;

        /**
         * Key material AES 256 (hex-encoded)
         */
        std::string aes256Key;

        /**
         * IV (hex-encoded)
         */
        std::string aes256Iv;

        /**
         * RSA private key (hex-encoded)
         */
        std::string rsaPrivateKey;

        /**
         * RSA public key (hex-encoded)
         */
        std::string rsaPublicKey;

        /**
         * Key material HMAC 224 (hex-encoded)
         */
        std::string hmac224Key;

        /**
         * Key material HMAC 256 (hex-encoded)
         */
        std::string hmac256Key;

        /**
         * Key material HMAC 384 (hex-encoded)
         */
        std::string hmac384Key;

        /**
         * Key material HMAC 256 (hex-encoded)
         */
        std::string hmac512Key;

        /**
         * Topic tags
         */
        std::map<std::string, std::string> tags;

        /**
         * Pending window in days
         */
        int pendingWindowInDays;

        /**
         * Scheduled deletion datetime
         */
        Poco::DateTime scheduledDeletion = Poco::DateTime(0);

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
         * @param mResult MongoDB document view.
         */
        void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
        friend std::ostream &operator<<(std::ostream &os, const Key &k);
    };

    typedef std::vector<Key> KeyList;

}// namespace AwsMock::Database::Entity::KMS

#endif// AWSMOCK_DB_ENTITY_KMS_KEY_H
