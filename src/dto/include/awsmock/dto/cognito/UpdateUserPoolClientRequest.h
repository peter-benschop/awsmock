//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_UPDATE_USERPOOL_CLIENT_REQUEST_H
#define AWSMOCK_DTO_COGNITO_UPDATE_USERPOOL_CLIENT_REQUEST_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/cognito/model/TokenValidityUnits.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Updates an existing user pool request
     *
     * Request to update an existing user pool.
     *
     * Example:
     * @code{.json}
     * {
     *   "AccessTokenValidity": number,
     *   "AllowedOAuthFlows": [ "string" ],
     *   "AllowedOAuthFlowsUserPoolClient": boolean,
     *   "AllowedOAuthScopes": [ "string" ],
     *   "AnalyticsConfiguration": {
     *      "ApplicationArn": "string",
     *      "ApplicationId": "string",
     *      "ExternalId": "string",
     *      "RoleArn": "string",
     *      "UserDataShared": boolean
     *   },
     *   "AuthSessionValidity": number,
     *   "CallbackURLs": [ "string" ],
     *   "ClientId": "string",
     *   "ClientName": "string",
     *   "DefaultRedirectURI": "string",
     *   "EnablePropagateAdditionalUserContextData": boolean,
     *   "EnableTokenRevocation": boolean,
     *   "ExplicitAuthFlows": [ "string" ],
     *   "IdTokenValidity": number,
     *   "LogoutURLs": [ "string" ],
     *   "PreventUserExistenceErrors": "string",
     *   "ReadAttributes": [ "string" ],
     *   "RefreshTokenValidity": number,
     *   "SupportedIdentityProviders": [ "string" ],
     *   "TokenValidityUnits": {
     *      "AccessToken": "string",
     *      "IdToken": "string",
     *      "RefreshToken": "string"
     *   },
     *   "UserPoolId": "string",
     *   "WriteAttributes": [ "string" ]
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct UpdateUserPoolClientRequest : Common::BaseRequest {

        /**
         * User pool ID
         */
        std::string userPoolId;

        /**
         * Client ID
         */
        std::string clientId;

        /**
         * Client name
         */
        std::string clientName;

        /**
         * Access token validity
         */
        int accessTokenValidity;

        /**
         * ID token validity
         */
        int idTokenValidity;

        /**
         * Refresh token validity
         */
        int refreshTokenValidity;

        /**
         * Auth session validity
         */
        int authSessionValidity;

        /**
         * Token validity units
         */
        TokenValidityUnits tokenValidityUnits;

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
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const UpdateUserPoolClientRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_UPDATE_USERPOOL_CLIENT_REQUEST_H
