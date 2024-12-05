//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SECRETSMANAGER_MESSAGE_H
#define AWSMOCK_DB_ENTITY_SECRETSMANAGER_MESSAGE_H

// C++ includes
#include <algorithm>
#include <string>
#include <vector>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/exception/exception.hpp>


// AwsMock includes
#include "awsmock/core/exception/DatabaseException.h"
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/NumberUtils.h>
#include <awsmock/entity/secretsmanager/RotationRules.h>

namespace AwsMock::Database::Entity::SecretsManager {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * SecretManager secrets entity.
     *
     * @author jens.vogt\@opitz-consulting.com
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
         * KMS key ID ID
         */
        std::string kmsKeyId;

        /**
         * Secret string
         */
        std::string secretString;

        /**
         * Base64 encoded secret binary
         */
        std::string secretBinary;

        /**
         * Version Id
         */
        std::string versionId;

        /**
         * Description
         */
        std::string description;

        /**
         * Owning service
         */
        std::string owningService;

        /**
         * Primary region
         */
        std::string primaryRegion;

        /**
         * RotationRules
         */
        RotationRules rotationRules;

        /**
         * Creation date
         */
        long createdDate = 0;

        /**
         * Deleted date
         */
        long deletedDate = 0;

        /**
         * Last access date
         */
        long lastAccessedDate = 0;

        /**
         * Last changed date
         */
        long lastChangedDate = 0;

        /**
         * Last rotation date
         */
        long lastRotatedDate = 0;

        /**
         * Next rotation date
         */
        long nextRotatedDate = 0;

        /**
         * Next rotation date
         */
        bool rotationEnabled = false;

        /**
         * Rotation lambda ARN
         */
        std::string rotationLambdaARN;

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
        void FromDocument(std::optional<bsoncxx::document::view> mResult);

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

    typedef std::vector<Secret> SecretList;

}// namespace AwsMock::Database::Entity::SecretsManager

#endif// AWSMOCK_DB_ENTITY_SECRETSMANAGER_MESSAGE_H
