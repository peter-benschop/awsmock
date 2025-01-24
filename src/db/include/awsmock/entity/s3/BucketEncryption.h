//
// Created by vogje01 on 06/09/2023.
//

#ifndef AWSMOCK_DB_ENTITY_S3_BUCKET_ENCRYPTION_H
#define AWSMOCK_DB_ENTITY_S3_BUCKET_ENCRYPTION_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/DatabaseException.h>

namespace AwsMock::Database::Entity::S3 {

    using bsoncxx::to_json;
    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * @brief S3 bucket encryption entity.
     *
     * Saves the bucket encryption parameters
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct BucketEncryption {

        /**
         * SSE algorithm
         */
        std::string sseAlgorithm;

        /**
         * KMS key ID
         */
        std::string kmsKeyId;

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document.
         */
        void FromDocument(const std::optional<view> &mResult);

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const BucketEncryption &q);
    };

}// namespace AwsMock::Database::Entity::S3

#endif// AWSMOCK_DB_ENTITY_S3_BUCKET_ENCRYPTION_H
