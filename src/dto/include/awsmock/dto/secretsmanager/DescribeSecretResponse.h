//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SECRETMANAGER_DESCRIBE_SECRET_RESPONSE_H
#define AWSMOCK_DTO_SECRETMANAGER_DESCRIBE_SECRET_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/secretsmanager/ReplicationStatus.h>
#include <awsmock/dto/secretsmanager/SecretTags.h>
#include <awsmock/dto/secretsmanager/VersionIdsToStages.h>

namespace AwsMock::Dto::SecretsManager {

    struct DescribeSecretResponse {

        /**
         * Region
         */
        std::string region;

        /**
         * Secret name
         */
        std::string name;

        /**
         * ARN
         */
        std::string arn;

        /**
         * Description
         */
        std::string description;

        /**
         * Last accessed date
         */
        double lastAccessDate;

        /**
         * Last accessed date
         */
        double lastChangedDate;

        /**
         * Last rotation date
         */
        double lastRotatedDate;

        /**
         * Last rotation date
         */
        double nextRotationDate;

        /**
         * Rotation enabled flag
         */
        bool rotationEnabled;

        /**
         * Replication status
         */
        ReplicationStatus replicationStatus;

        /**
         * Version IDs to stages
         */
        VersionIdsToStages versionIdsToStages;

        /**
         * Map of Tags
         */
        std::map<std::string, std::string> tags;

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
        friend std::ostream &operator<<(std::ostream &os, const DescribeSecretResponse &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETMANAGER_DESCRIBE_SECRET_RESPONSE_H
