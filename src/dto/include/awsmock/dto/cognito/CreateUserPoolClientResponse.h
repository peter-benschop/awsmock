//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_CLIENT_RESPONSE_H
#define AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_CLIENT_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/cognito/model/UserPoolClient.h>
#include <awsmock/dto/common/BaseDto.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Create user pool client response
     *
     * Example:
     * @code{.json}
     * {
     *   "UserPoolClient": {
     *      "AccessTokenValidity": number,
     *      "AllowedOAuthFlows": [ "string" ],
     *      "AllowedOAuthFlowsUserPoolClient": boolean,
     *      "AllowedOAuthScopes": [ "string" ],
     *      "AnalyticsConfiguration": {
     *         "ApplicationArn": "string",
     *         "ApplicationId": "string",
     *         "ExternalId": "string",
     *         "RoleArn": "string",
     *         "UserDataShared": boolean
     *      },
     *      "AuthSessionValidity": number,
     *      "CallbackURLs": [ "string" ],
     *      "ClientId": "string",
     *      "ClientName": "string",
     *      "ClientSecret": "string",
     *      "CreationDate": number,
     *      "DefaultRedirectURI": "string",
     *      "EnablePropagateAdditionalUserContextData": boolean,
     *      "EnableTokenRevocation": boolean,
     *      "ExplicitAuthFlows": [ "string" ],
     *      "IdTokenValidity": number,
     *      "LastModifiedDate": number,
     *      "LogoutURLs": [ "string" ],
     v      "PreventUserExistenceErrors": "string",
     *      "ReadAttributes": [ "string" ],
     *      "RefreshTokenValidity": number,
     *      "SupportedIdentityProviders": [ "string" ],
     *      "TokenValidityUnits": {
     *         "AccessToken": "string",
     *         "IdToken": "string",
     *         "RefreshToken": "string"
     *      },
     *      "UserPoolId": "string",
     *      "WriteAttributes": [ "string" ]
     *   }
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CreateUserPoolClientResponse final : Common::BaseDto<CreateUserPoolClientResponse> {

        /**
         * @brief User group client
         */
        UserPoolClient userGroupClient;

        /**
         * @brief Convert to a JSON string.
         *
         * @return json string
         */
        std::string ToJson() const override;
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_CLIENT_RESPONSE_H
