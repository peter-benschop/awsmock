//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_UPDATE_USERPOOL_REQUEST_H
#define AWSMOCK_DTO_COGNITO_UPDATE_USERPOOL_REQUEST_H

// C++ standard includes
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
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
     *   "AccountRecoverySetting": {
     *      "RecoveryMechanisms": [
     *         {
     *            "Name": "string",
     *            "Priority": number
     *         }
     *      ]
     *   },
     *   "AdminCreateUserConfig": {
     *      "AllowAdminCreateUserOnly": boolean,
     *      "InviteMessageTemplate": {
     *         "EmailMessage": "string",
     *         "EmailSubject": "string",
     *         "SMSMessage": "string"
     *      },
     *      "UnusedAccountValidityDays": number
     *   },
     *   "AutoVerifiedAttributes": [ "string" ],
     *   "DeletionProtection": "string",
     *   "DeviceConfiguration": {
     *      "ChallengeRequiredOnNewDevice": boolean,
     *      "DeviceOnlyRememberedOnUserPrompt": boolean
     *   },
     *   "EmailConfiguration": {
     *      "ConfigurationSet": "string",
     *      "EmailSendingAccount": "string",
     *      "From": "string",
     *      "ReplyToEmailAddress": "string",
     *      "SourceArn": "string"
     *   },
     *   "EmailVerificationMessage": "string",
     v   "EmailVerificationSubject": "string",
     *   "LambdaConfig": {
     *      "CreateAuthChallenge": "string",
     *      "CustomEmailSender": {
     *         "LambdaArn": "string",
     *         "LambdaVersion": "string"
     *      },
     *      "CustomMessage": "string",
     *      "CustomSMSSender": {
     *         "LambdaArn": "string",
     *         "LambdaVersion": "string"
     *      },
     *      "DefineAuthChallenge": "string",
     *      "KMSKeyID": "string",
     *      "PostAuthentication": "string",
     *      "PostConfirmation": "string",
     *      "PreAuthentication": "string",
     *      "PreSignUp": "string",
     *      "PreTokenGeneration": "string",
     *      "PreTokenGenerationConfig": {
     *         "LambdaArn": "string",
     *         "LambdaVersion": "string"
     *      },
     *      "UserMigration": "string",
     *      "VerifyAuthChallengeResponse": "string"
     *   },
     *   "MfaConfiguration": "string",
     *   "Policies": {
     *      "PasswordPolicy": {
     *         "MinimumLength": number,
     *         "RequireLowercase": boolean,
     *         "RequireNumbers": boolean,
     *         "RequireSymbols": boolean,
     *         "RequireUppercase": boolean,
     *         "TemporaryPasswordValidityDays": number
     *      }
     *   },
     *   "SmsAuthenticationMessage": "string",
     *   "SmsConfiguration": {
     *      "ExternalId": "string",
     *      "SnsCallerArn": "string",
     *      "SnsRegion": "string"
     *   },
     *   "SmsVerificationMessage": "string",
     *   "UserAttributeUpdateSettings": {
     *      "AttributesRequireVerificationBeforeUpdate": [ "string" ]
     *   },
     *   "UserPoolAddOns": {
     *      "AdvancedSecurityMode": "string"
     *   },
     *   "UserPoolId": "string",
     *   "UserPoolTags": {
     *      "string" : "string"
     *   },
     *   "VerificationMessageTemplate": {
     *      "DefaultEmailOption": "string",
     *      "EmailMessage": "string",
     *      "EmailMessageByLink": "string",
     *      "EmailSubject": "string",
     *      "EmailSubjectByLink": "string",
     *      "SmsMessage": "string"
     *   }
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct UpdateUserPoolRequest : Common::BaseRequest {

        /**
         * User pool ID
         */
        std::string userPoolId;

        /**
         * User pool tags
         */
        std::map<std::string, std::string> tags;

        /**
         * Convert from a JSON object.
         *
         * @param jsonString json string object
         */
        void FromJson(const std::string &jsonString);

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
        friend std::ostream &operator<<(std::ostream &os, const UpdateUserPoolRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_UPDATE_USERPOOL_REQUEST_H
