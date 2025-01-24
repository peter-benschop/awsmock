//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_ROTATE_SECRET_RESPONSE_H
#define AWSMOCK_CORE_DTO_ROTATE_SECRET_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Rotate a secret value response.
     *
     * Example:
     * @code{.json}
     * {
     *   "ARN": "string",
     *   "Name": "string",
     *   "VersionId": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct RotateSecretResponse {

        /**
         * Region
         */
        std::string region;

        /**
         * Secret ARN
         */
        std::string arn;

        /**
         * Version ID
         */
        std::string versionId;

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
        friend std::ostream &operator<<(std::ostream &os, const RotateSecretResponse &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_CORE_DTO_ROTATE_SECRET_RESPONSE_H
