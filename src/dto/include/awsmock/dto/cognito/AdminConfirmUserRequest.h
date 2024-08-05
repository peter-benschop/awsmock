//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_CONFIRM_USER_REQUEST_H
#define AWSMOCK_DTO_COGNITO_CONFIRM_USER_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Confirm user request
     *
     * Example:
     * @code{.json}
     * {
     *   "AnalyticsMetadata": {
     *      "AnalyticsEndpointId": "string"
     *   },
     *   "ClientId": "string",
     *   "ClientMetadata": {
     *      "string" : "string"
     *   },
     *   "ConfirmationCode": "string",
     *   "ForceAliasCreation": boolean,
     *   "SecretHash": "string",
     *   "UserContextData": {
     *      "EncodedData": "string",
     *      "IpAddress": "string"
     *   },
     *   "Username": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct AdminConfirmUserRequest : public Dto::Common::BaseRequest {

        /**
         * Name of the user
         */
        std::string userName;

        /**
         * User pool ID
         */
        std::string userPoolId;

        /**
         * Client metadata
         */
        std::map<std::string, std::string> clientMetadata;
        
        /**
         * Convert from a JSON object.
         *
         * @param payload json string object
         */
        void FromJson(const std::string &payload);

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const AdminConfirmUserRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_CONFIRM_USER_REQUEST_H
