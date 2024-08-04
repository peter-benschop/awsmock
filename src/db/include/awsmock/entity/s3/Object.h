//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_OBJECT_H
#define AWSMOCK_DB_ENTITY_S3_OBJECT_H

// C++ includes
#include <chrono>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database::Entity::S3 {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;
    using std::chrono::system_clock;

    /**
     * @brief S3 object entity
     *
     * @author jens.vogt\@opitz-consulting.com
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
        system_clock::time_point created = system_clock::now();

        /**
         * Last modification date
         */
        system_clock::time_point modified = system_clock::now();

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
         * @param object object entity
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Object &object);
    };

    typedef struct Object Object;
    typedef std::vector<Object> ObjectList;

}// namespace AwsMock::Database::Entity::S3
// namespace AwsMock::Database::S3::Entity

#endif//AWSMOCK_DB_ENTITY_S3_OBJECT_H
