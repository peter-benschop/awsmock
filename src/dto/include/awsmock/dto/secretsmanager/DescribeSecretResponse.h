//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SECRETMANAGER_DESCRIBE_SECRET_RESPONSE_H
#define AWSMOCK_DTO_SECRETMANAGER_DESCRIBE_SECRET_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMoc includes
#include "awsmock/core/JsonException.h"
#include <awsmock/core/JsonUtils.h>
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
     * Version IDs to stages
     */
        SecretTags tags;

        /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
        [[nodiscard]] std::string ToJson() const;

        /**
     * Convert from JSON representation
     *
     * @param jsonString JSON string
     */
        void FromJson(const std::string &jsonString);

        /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
        [[nodiscard]] std::string ToString() const;

        /**
     * Stream provider.
     *
     * @return output stream
     */
        friend std::ostream &operator<<(std::ostream &os, const DescribeSecretResponse &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETMANAGER_DESCRIBE_SECRET_RESPONSE_H
