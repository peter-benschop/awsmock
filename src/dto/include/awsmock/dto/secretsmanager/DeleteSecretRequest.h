//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_DELETE_SECRET_REQUEST_H
#define AWSMOCK_CORE_DTO_DELETE_SECRET_REQUEST_H

// C++ standard includes
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    struct DeleteSecretRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Secret name
         */
        std::string name;

        /**
         * AWS request ID
         */
        std::string requestId;

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
        friend std::ostream &operator<<(std::ostream &os, const DeleteSecretRequest &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_CORE_DTO_DELETE_SECRET_REQUEST_H
