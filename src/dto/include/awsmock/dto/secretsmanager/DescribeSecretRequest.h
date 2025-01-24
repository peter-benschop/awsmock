//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_DESCRIBE_SECRET_REQUEST_H
#define AWSMOCK_DTO_SECRETSMANAGER_DESCRIBE_SECRET_REQUEST_H

// C++ standard includes
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    struct DescribeSecretRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Secret Id
         */
        std::string secretId;

        /**
         * AWS request ID
         */
        std::string requestId;

        /**
         * Converts the DTO to a JSON representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Converts the JSON string to DTO.
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const DescribeSecretRequest &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETSMANAGER_DESCRIBE_SECRET_REQUEST_H
