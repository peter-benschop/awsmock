//
// Created by vogje01 on 06/09/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_BUCKET_NOTIFICATION_H
#define AWSMOCK_DB_ENTITY_S3_BUCKET_NOTIFICATION_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>

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
         * @brief Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const BucketNotification &q);
    };

}// namespace AwsMock::Database::Entity::S3

#endif// AWSMOCK_DB_ENTITY_S3_BUCKET_NOTIFICATION_H
