//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SECRETMANAGER_LIST_SECRETS_RESPONSE_H
#define AWSMOCK_DTO_SECRETMANAGER_LIST_SECRETS_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/secretsmanager/model/Secret.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * List secrets response
     *
     * Example:
     * @code{.json}
     * {
     *    "NextToken": "string",
     *    "SecretList": [
     *    .....
     *   ]
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListSecretsResponse {

        /**
         * Region
         */
        std::string region;

        /**
         * Next token
         */
        std::string nextToken;

        /**
         * List of secrets
         */
        std::vector<Secret> secretList;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const ListSecretsResponse &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETMANAGER_LIST_SECRETS_RESPONSE_H
