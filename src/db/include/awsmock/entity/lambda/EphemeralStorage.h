//
// Created by vogje01 on 03/09/2023.
//

#ifndef AWSMOCK_ENTITY_LAMBDA_EPHEMERALSTORAGE_H
#define AWSMOCK_ENTITY_LAMBDA_EPHEMERALSTORAGE_H

// C++ includes
#include <sstream>
#include <string>
#include <vector>

// Poco includes
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/array/view.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/stdx.hpp>

namespace AwsMock::Database::Entity::Lambda {

    using bsoncxx::to_json;
    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * Lambda ephemeral storage entity
     *
     * @author jens.vogt@opitz-consulting.com
     */
    struct EphemeralStorage {

        /**
         * Temporary disk space in MB. Default: 512 MB, Range: 512 - 10240 MB
         */
        long size = 512;

        /**
         * Converts the MongoDB document to an entity
         *
         * @param mResult database document.
         */
        [[maybe_unused]] void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

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
        friend std::ostream &operator<<(std::ostream &os, const EphemeralStorage &m);
    };

}// namespace AwsMock::Database::Entity::Lambda

#endif// AWSMOCK_ENTITY_LAMBDA_EPHEMERALSTORAGE_H
