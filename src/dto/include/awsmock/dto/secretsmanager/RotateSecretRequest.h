//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_ROTATE_SECRET_REQUEST_H
#define AWSMOCK_CORE_DTO_ROTATE_SECRET_REQUEST_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/secretsmanager/RotationRules.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Rotate a secret value request.
     *
     * Example:
     * @code{.json}
     * {
     *   "ClientRequestToken": "string",
     *   "RotateImmediately": boolean,
     *   "RotationLambdaARN": "string",
     *   "RotationRules": {
     *     "AutomaticallyAfterDays": number,
     *     "Duration": "string",
     *     "ScheduleExpression": "string"
     *   },
     *   "SecretId": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct RotateSecretRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Secret ID
         */
        std::string secretId;

        /**
         * Client request token
         */
        std::string clientRequestToken;

        /**
         * Rotation lambda ARN
         */
        std::string rotationLambdaARN;

        /**
         * Rotate immediately
         */
        bool rotateImmediately;

        /**
         * Rotation rules
         */
        RotationRules rotationRules;

        /**
         * AWS request ID
         */
        std::string requestId;

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
        friend std::ostream &operator<<(std::ostream &os, const RotateSecretRequest &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_CORE_DTO_ROTATE_SECRET_REQUEST_H
