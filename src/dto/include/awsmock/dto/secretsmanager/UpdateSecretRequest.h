//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_UPDATE_SECRET_REQUEST_H
#define AWSMOCK_CORE_DTO_UPDATE_SECRET_REQUEST_H

// C++ standard includes
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Update the secret values request.
     *
     * Example:
     * @code{.json}
     * {
     *   "ClientRequestToken": "string",
     *   "Description": "string",
     *   "KmsKeyId": "string",
     *   "SecretBinary": blob,
     *   "SecretId": "string",
     *   "SecretString": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct UpdateSecretRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Secret ID
         */
        std::string secretId;

        /**
         * KMS key ID
         */
        std::string kmsKeyId;

        /**
         * Description
         */
        std::string description;

        /**
         * Secret string
         */
        std::string secretString;

        /**
         * Secret binary
         */
        std::string secretBinary;

        /**
         * AWS request ID
         */
        std::string requestId;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the JSON string to DTO.
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

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
        friend std::ostream &operator<<(std::ostream &os, const UpdateSecretRequest &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_CORE_DTO_UPDATE_SECRET_REQUEST_H
