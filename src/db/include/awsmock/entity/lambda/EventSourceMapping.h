//
// Created by vogje01 on 03/09/2023.
//

#ifndef AWSMOCK_DB_ENTITY_LAMBDA_EVENT_SOURCE_MAPPING_H
#define AWSMOCK_DB_ENTITY_LAMBDA_EVENT_SOURCE_MAPPING_H

// C++ includes
#include <string>

// MongoDB includes
#include <awsmock/core/BsonUtils.h>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>


namespace AwsMock::Database::Entity::Lambda {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * @brief Lambda event source mapping
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct EventSourceMapping {

        /**
         * Event source ARN
         */
        std::string eventSourceArn;

        /**
         * Batch size
         */
        int batchSize;

        /**
         * Maximum BatchingWindowInSeconds
         */
        int maximumBatchingWindowInSeconds;

        /**
         * Enabled
         */
        bool enabled;

        /**
         * UUID
         */
        std::string uuid;

        /**
         * @brief Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document view.
         */
        [[maybe_unused]] void FromDocument(std::optional<bsoncxx::document::view> mResult);

        /**
         * @brief Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @param os output stream
         * @param e event source mapping
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const EventSourceMapping &e);
    };

}// namespace AwsMock::Database::Entity::Lambda

#endif// AWSMOCK_DB_ENTITY_LAMBDA_EVENT_SOURCE_MAPPING_H
