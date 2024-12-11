//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_INITIATE_AUTH_REQUEST_H
#define AWSMOCK_DTO_COGNITO_INITIATE_AUTH_REQUEST_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/cognito/model/AuthFlow.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Initiate authentication request
     *
     * Example:
     * @code{.json}
     * {
     *   "AnalyticsMetadata": {
     *      "AnalyticsEndpointId": "string"
     *   },
     *   "AuthFlow": "string",
     *   "AuthParameters": {
     *      "string" : "string"
     *   },
     *   "ClientId": "string",
     *   "ClientMetadata": {
     *      "string" : "string"
     *   },
     *   "UserContextData": {
     *      "EncodedData": "string",
     *      "IpAddress": "string"
     *   }
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct InitiateAuthRequest : Common::BaseRequest {

        /**
         * Auth flow
         *
         * Valid Values: USER_SRP_AUTH | REFRESH_TOKEN_AUTH | REFRESH_TOKEN | CUSTOM_AUTH | ADMIN_NO_SRP_AUTH | USER_PASSWORD_AUTH | ADMIN_USER_PASSWORD_AUTH
         */
        AuthFlowType authFlow;

        /**
         * Client ID
         */
        std::string clientId;

        /**
         * Auth parameters
         */
        std::map<std::string, std::string> authParameters;

        /**
         * Client metadata
         */
        std::map<std::string, std::string> clientMetaData;

        /**
         * @brief Convert from a JSON object.
         *
         * @param jsonString json string object
         */
        void FromJson(const std::string &jsonString);

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
         * @brief Returns the username
         *
         * @return user ID
         */
        std::string GetUserId();

        /**
         * @brief Returns the user password
         *
         * @return user password
         */
        std::string GetPassword();

        /**
         * @brief Returns the client secret from the AuthParameters
         *
         * @return client secret
         */
        std::string GetClientSecret();

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const InitiateAuthRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_INITIATE_AUTH_REQUEST_H
