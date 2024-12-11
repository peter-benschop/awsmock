//
// Created by vogje01 on 4/9/24.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_GET_SECRET_VALUE_RESPONSE_H
#define AWSMOCK_DTO_SECRETSMANAGER_GET_SECRET_VALUE_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Get a secret value
     *
     * Example:
     * @code{.json}
     * {
     *   "Name": "string",
     *   "ARN": "string",
     *   "CreatedDate": number,
     *   "SecretBinary": blob,
     *   "SecretString": "string",
     *   "VersionId": "string",
     *   "VersionStages": [ "string" ]
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct GetSecretValueResponse {

        /*+
         * Name
         */
        std::string name;

        /**
         * ARN
         */
        std::string arn;

        /**
         * Created date
         */
        double createdDate = -1;

        /**
         * Secret string
         */
        std::string secretString;

        /**
         * Base64 encoded secret binary data
         */
        std::string secretBinary;

        /**
         * Version ID
         */
        std::string versionId;

        /**
         * Version ID
         */
        std::vector<std::string> versionStages;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
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
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const GetSecretValueResponse &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETSMANAGER_GET_SECRET_VALUE_RESPONSE_H
