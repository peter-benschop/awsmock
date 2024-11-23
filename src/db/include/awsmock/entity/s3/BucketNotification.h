//
// Created by vogje01 on 06/09/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_BUCKET_NOTIFICATION_H
#define AWSMOCK_DB_ENTITY_S3_BUCKET_NOTIFICATION_H

// C++ includes
#include <string>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <bsoncxx/json.hpp>

namespace AwsMock::Database::Entity::S3 {

    using bsoncxx::to_json;
    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * S3 bucket notification entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct BucketNotification {

        /**
         * Event
         */
        std::string event;

        /**
         * Notification ID
         */
        std::string notificationId;

        /**
         * Queue ARN
         */
        std::string queueArn;

        /**
         * Lambda ARN
         */
        std::string lambdaArn;

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

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
        friend std::ostream &operator<<(std::ostream &os, const BucketNotification &q);
    };

}// namespace AwsMock::Database::Entity::S3

#endif// AWSMOCK_DB_ENTITY_S3_BUCKET_NOTIFICATION_H
