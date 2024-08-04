//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_REQUEST_H
#define AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_REQUEST_H

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
     * @brief Create user pool request
     *
     * Request to create a new user pool.
     *
     * Example:
     * @code{.json}
     * {
     *   "AccountRecoverySetting": {
     *     "RecoveryMechanisms": [
     *        {
     *           "Name": "string",
     *           "Priority": number
     *        }
     *     ]
     *   },
     *   "AdminCreateUserConfig": {
     *     "AllowAdminCreateUserOnly": boolean,
     *     "InviteMessageTemplate": {
     *        "EmailMessage": "string",
     *        "EmailSubject": "string",
     *        "SMSMessage": "string"
     *     },
     *     "UnusedAccountValidityDays": number
     *  },
     *  "AliasAttributes": [ "string" ],
     *  "AutoVerifiedAttributes": [ "string" ],
     *  "DeletionProtection": "string",
     *  "DeviceConfiguration": {
     *     "ChallengeRequiredOnNewDevice": boolean,
     *     "DeviceOnlyRememberedOnUserPrompt": boolean
     *   },
     *   "EmailConfiguration": {
     *      "ConfigurationSet": "string",
     *      "EmailSendingAccount": "string",
     *      "From": "string",
     *      "ReplyToEmailAddress": "string",
     *      "SourceArn": "string"
     *   },
     *   "EmailVerificationMessage": "string",
     *   "EmailVerificationSubject": "string",
     *   "LambdaConfig": {
     *      "CreateAuthChallenge": "string",
     *      "CustomEmailSender": {
     *        "LambdaArn": "string",
     *        "LambdaVersion": "string"
     *      },
     *      "CustomMessage": "string",
     *      "CustomSMSSender": {
     *      "LambdaArn": "string",
     *        "LambdaVersion": "string"
     *      },
     *      "DefineAuthChallenge": "string",
     *      "KMSKeyID": "string",
     *      "PostAuthentication": "string",
     *        "PostConfirmation": "string",
     *        "PreAuthentication": "string",
     *        "PreSignUp": "string",
     *        "PreTokenGeneration": "string",
     *        "PreTokenGenerationConfig": {
     *          "LambdaArn": "string",
     *          "LambdaVersion": "string"
     *        },
     *        "UserMigration": "string",
     *        "VerifyAuthChallengeResponse": "string"
     *      },
     *       "MfaConfiguration": "string",
     *       "Policies": {
     *          "PasswordPolicy": {
     *             "MinimumLength": number,
     *             "RequireLowercase": boolean,
     *             "RequireNumbers": boolean,
     *             "RequireSymbols": boolean,
     *             "RequireUppercase": boolean,
     *             "TemporaryPasswordValidityDays": number
     *          }
     *       },
     *       "PoolName": "string",
     *       "Schema": [
     *          {
     *             "AttributeDataType": "string",
     *             "DeveloperOnlyAttribute": boolean,
     *             "Mutable": boolean,
     *             "Name": "string",
     *             "NumberAttributeConstraints": {
     *                "MaxValue": "string",
     *                "MinValue": "string"
     *             },
     *             "Required": boolean,
     *             "StringAttributeConstraints": {
     *                "MaxLength": "string",
     *                "MinLength": "string"
     *             }
     *          }
     *       ],
     *       "SmsAuthenticationMessage": "string",
     *       "SmsConfiguration": {
     *          "ExternalId": "string",
     *          "SnsCallerArn": "string",
     *          "SnsRegion": "string"
     *       },
     *       "SmsVerificationMessage": "string",
     *       "UserAttributeUpdateSettings": {
     *       "AttributesRequireVerificationBeforeUpdate": [ "string" ]
     *    },
     *    "UsernameAttributes": [ "string" ],
     *    "UsernameConfiguration": {
     *       "CaseSensitive": boolean
     *    },
     *    "UserPoolAddOns": {
     *       "AdvancedSecurityMode": "string"
     *    },
     *    "UserPoolTags": {
     *      "string" : "string"
     *    },
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
    struct CreateUserPoolRequest : public Dto::Common::BaseRequest {

        /**
         * Name of the user pool
         */
        std::string name;

        /**
         * Domain of the user pool
         */
        std::string domain;

        /**
         * Tags
         */
        std::map<std::string, std::string> tags;

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
        friend std::ostream &operator<<(std::ostream &os, const CreateUserPoolRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_REQUEST_H
