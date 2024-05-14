//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_UPDATE_SECRET_REQUEST_H
#define AWSMOCK_CORE_DTO_UPDATE_SECRET_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMoc includes
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Update the secret values request.
     *
     * Example:
     * @code{.json}
     * {
     *   "ClientRequestToken": "string",
     *   "Description": "string",
     *   "KmsKeyId": "string",
     *   "SecretBinary": blob,
     *   "SecretId": "string",
     *   "SecretString": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct UpdateSecretRequest {

        /**
     * Region
     */
        std::string region;

        /**
     * Secret ID
     */
        std::string secretId;

        /**
     * KMS key ID
     */
        std::string kmsKeyId;

        /**
     * Description
     */
        std::string description;

        /**
     * Secret string
     */
        std::string secretString;

        /**
     * Secret binary
     */
        std::string secretBinary;

        /**
     * AWS request ID
     */
        std::string requestId;

        /**
     * Converts the DTO to a JSON representation.
     *
     * @return DTO as string for logging.
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
        friend std::ostream &operator<<(std::ostream &os, const UpdateSecretRequest &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_CORE_DTO_UPDATE_SECRET_REQUEST_H
