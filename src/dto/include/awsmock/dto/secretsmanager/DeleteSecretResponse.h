//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SECRETMANAGER_DELETE_SECRET_RESPONSE_H
#define AWSMOCK_DTO_SECRETMANAGER_DELETE_SECRET_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SecretsManager {


    /**
     * Return structure for the delete secret request.
     *
     * Example:
     * @code{.json}
     * {
     *   "ARN": "string",
     *   "DeletionDate": number,
     *   "Name": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct DeleteSecretResponse {

        /**
         * Region
         */
        std::string region;

        /**
         * Secret name
         */
        std::string name;

        /**
         * Secret ARN
         */
        std::string arn;

        /**
         * Secret deletion date
         */
        double deletionDate = -1;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert from JSON representation
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
        friend std::ostream &operator<<(std::ostream &os, const DeleteSecretResponse &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETMANAGER_DELETE_SECRET_RESPONSE_H
