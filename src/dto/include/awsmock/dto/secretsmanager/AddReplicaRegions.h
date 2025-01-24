//
// Created by vogje01 on 4/8/24.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_ADD_REPLICA_REGIONS_H
#define AWSMOCK_DTO_SECRETSMANAGER_ADD_REPLICA_REGIONS_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Secrets manager replication status.
     *
     * Example:
     * @code{.json}
     * "AddReplicaRegions": [
     *   {
     *     "KmsKeyId": "string",
     *     "Region": "string"
     *   }
     * ],
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct AddReplicaRegions {

        /**
         * AWS Region
         */
        std::string region;

        /**
         * KMS key ID
         */
        std::string kmsKeyId;

        /**
         * @brief Converts the DTO to a JSON object.
         *
         * @return DTO as JSON object
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts a JSON representation to s DTO.
         *
         * @param document JSON object.
         */
        void FromJson(const view_or_value<view, value> &document);

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
        friend std::ostream &operator<<(std::ostream &os, const AddReplicaRegions &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETSMANAGER_ADD_REPLICA_REGIONS_H
