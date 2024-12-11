//
// Created by vogje01 on 4/8/24.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_REPLICATION_STATUS_H
#define AWSMOCK_DTO_SECRETSMANAGER_REPLICATION_STATUS_H

// C++ standard includes
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Secrets manager replication status.
     *
     * Example:
     * @code{.json}
     * {
     *   "KmsKeyId": "string",
     *   "LastAccessedDate": number,
     *   "Region": "string",
     *   "Status": "string",
     *   "StatusMessage": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ReplicationStatus {

        /**
         * Region
         */
        std::string region;

        /**
         * ARN
         */
        std::string arn;

        /**
         * KMS key ID
         */
        std::string kmsKeyId;

        /**
         * Last access date
         */
        double lastAccessedDate;

        /**
         * Status
         */
        std::string status;

        /**
         * Status message
         */
        std::string statusMessage;

        /**
         * @brief Converts the DTO to a JSON object.
         *
         * @return DTO as string
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts a JSON representation to s DTO.
         *
         * @param document JSON object.
         */
        void FromDocument(const view_or_value<view, value> &document);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const ReplicationStatus &r);
    };

}//namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETSMANAGER_REPLICATION_STATUS_H
