//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_CLIENT_REQUEST_H
#define AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_CLIENT_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/cognito/model/CustomDomainConfig.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Create user pool client request
     *
     * Request to create a new user pool client.
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
     *   "ClientName": "string",
     *   "DefaultRedirectURI": "string",
     *   "EnablePropagateAdditionalUserContextData": boolean,
     *   "EnableTokenRevocation": boolean,
     *   "ExplicitAuthFlows": [ "string" ],
     *   "GenerateSecret": boolean,
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
    struct CreateUserPoolClientRequest : public Dto::Common::BaseRequest {

        /**
         * User pool of the domain
         */
        std::string userPoolId;

        /**
         * Client name
         */
        std::string clientName;

        /**
         * Generate secret flag
         */
        bool generateSecret;

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
        friend std::ostream &operator<<(std::ostream &os, const CreateUserPoolClientRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_CLIENT_REQUEST_H
