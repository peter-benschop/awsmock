//
// Created by vogje01 on 12/10/23.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_REDRIVE_POLICY_H
#define AWSMOCK_DB_ENTITY_SQS_REDRIVE_POLICY_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Database::Entity::SQS {

    /**
     * SQS queue re-drive policy entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct RedrivePolicy {

        /**
         * Dead letter queue target ARN
         */
        std::string deadLetterTargetArn;

        /**
         * Maximal number of retries, before the message will be send to the DQL
         */
        int maxReceiveCount = 0;

        /**
         * @brief Parse values from a JSON stream
         *
         * @param jsonString json input stream
         */
        void FromJson(const std::string &jsonString);

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document.
         */
        [[maybe_unused]] void FromDocument(const std::optional<view> &mResult);

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
         * @param r redrive policy
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const RedrivePolicy &r);
    };

}// namespace AwsMock::Database::Entity::SQS

#endif// AWSMOCK_DB_ENTITY_SQS_REDRIVE_POLICY_H
