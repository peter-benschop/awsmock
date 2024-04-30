//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_CREATE_SECRET_REQUEST_H
#define AWSMOCK_DTO_SECRETSMANAGER_CREATE_SECRET_REQUEST_H

// C++ standard includes
#include <map>
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include "awsmock/core/JsonException.h"
#include <awsmock/core/JsonUtils.h>
#include <awsmock/dto/secretsmanager/SecretTags.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Example:
     *
     * @verbatim
     * {
     *   "Name": "test",
     *   "ClientRequestToken": "8b0e8777-4c9a-4621-9bd7-a6449b24c3a5"
     * }
     * @endverbatim
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CreateSecretRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Secret name
         */
        std::string name;

        /**
         * Client request token
         */
        std::string clientRequestToken;

        /**
         * Description
         */
        std::string description;

        /**
         * Secret string
         */
        std::string secretString;

        /**
         * Base64 encoded secret binary data
         */
        std::string secretBinary;

        /**
         * Force overwrite flag
         */
        bool forceOverwriteReplicaSecret;

        /**
         * KMS key ID
         */
        std::string kmsKeyId;

        /**
         * Tags
         */
        SecretTags tags;

        /**
         * AWS request ID
         */
        std::string requestId;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
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
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const CreateSecretRequest &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETSMANAGER_CREATE_SECRET_REQUEST_H
