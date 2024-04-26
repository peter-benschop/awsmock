//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SECRETMANAGER_DELETE_SECRET_RESPONSE_H
#define AWSMOCK_DTO_SECRETMANAGER_DELETE_SECRET_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMoc includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SecretsManager {


    /**
     * Return structure for the delete secret request.
     *
     * Example:
     *
     * <pre>
     * {
     *   "ARN": "string",
     *   "DeletionDate": number,
     *   "Name": "string"
     * }
     * </pre>
     *
     * @author jens.vogt@opitz-consulting.com
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
        friend std::ostream &operator<<(std::ostream &os, const DeleteSecretResponse &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETMANAGER_DELETE_SECRET_RESPONSE_H
