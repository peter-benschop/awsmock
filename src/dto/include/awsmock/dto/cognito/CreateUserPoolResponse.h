//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_RESPONSE_H
#define AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include "awsmock/core/exception/JsonException.h"
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Create user pool response
     *
     * Example:
     * @code{.json}
     * {
     *   "UserPool": {
     *     "AccountRecoverySetting": {
     *       "RecoveryMechanisms": [
     *         {
     *           "Name": "string",
     *           "Priority": number
     *         }
     *       ]
     *    },
     *    "AdminCreateUserConfig": {
     *      "AllowAdminCreateUserOnly": boolean,
     *      "InviteMessageTemplate": {
     *        "EmailMessage": "string",
     *        "EmailSubject": "string",
     *        "SMSMessage": "string"
     *      },
     *      "UnusedAccountValidityDays": number
     *    },
     *    "AliasAttributes": [ "string" ],
     *    "Arn": "string",
     *    "AutoVerifiedAttributes": [ "string" ],
     *    "CreationDate": number,
     *    "CustomDomain": "string",
     *    "DeletionProtection": "string",
     *    "DeviceConfiguration": {
     *      "ChallengeRequiredOnNewDevice": boolean,
     *      "DeviceOnlyRememberedOnUserPrompt": boolean
     *   },
     *   "Domain": "string",
     *   "EmailConfiguration": {
     *      "ConfigurationSet": "string",
     *      "EmailSendingAccount": "string",
     *      "From": "string",
     *      "ReplyToEmailAddress": "string",
     *      "SourceArn": "string"
     *     },
     *     "EmailConfigurationFailure": "string",
     *      "EmailVerificationMessage": "string",
     *      "EmailVerificationSubject": "string",
     *      "EstimatedNumberOfUsers": number,
     *      "Id": "string",
     *      "LambdaConfig": {
     *        "CreateAuthChallenge": "string",
     *          "CustomEmailSender": {
     *          "LambdaArn": "string",
     *          "LambdaVersion": "string"
     *        },
     *        "CustomMessage": "string",
     *        "CustomSMSSender": {
     *           "LambdaArn": "string",
     *           "LambdaVersion": "string"
     *        },
     *         "DefineAuthChallenge": "string",
     *         "KMSKeyID": "string",
     *         "PostAuthentication": "string",
     *         "PostConfirmation": "string",
     *         "PreAuthentication": "string",
     *         "PreSignUp": "string",
     *         "PreTokenGeneration": "string",
     *         "PreTokenGenerationConfig": {
     *           "LambdaArn": "string",
     *           "LambdaVersion": "string"
     *          },
     *         "UserMigration": "string",
     *         "VerifyAuthChallengeResponse": "string"
     *        },
     *        "LastModifiedDate": number,
     *        "MfaConfiguration": "string",
     *        "Name": "string",
     *        "Policies": {
     *        "PasswordPolicy": {
     *          "MinimumLength": number,
     *          "RequireLowercase": boolean,
     *          "RequireNumbers": boolean,
     *          "RequireSymbols": boolean,
     *          "RequireUppercase": boolean,
     *          "TemporaryPasswordValidityDays": number
     *        }
     *      },
     *      "SchemaAttributes": [
     *        {
     *           "AttributeDataType": "string",
     *           "DeveloperOnlyAttribute": boolean,
     *           "Mutable": boolean,
     *           "Name": "string",
     *           "NumberAttributeConstraints": {
     *              "MaxValue": "string",
     *              "MinValue": "string"
     *           },
     *           "Required": boolean,
     *           "StringAttributeConstraints": {
     *              "MaxLength": "string",
     *              "MinLength": "string"
     *           }
     *         }
     *       ],
     *       "SmsAuthenticationMessage": "string",
     *       "SmsConfiguration": {
     *         "ExternalId": "string",
     *         "SnsCallerArn": "string",
     *         "SnsRegion": "string"
     *       },
     *       "SmsConfigurationFailure": "string",
     *       "SmsVerificationMessage": "string",
     *       "Status": "string",
     *       "UserAttributeUpdateSettings": {
     *         "AttributesRequireVerificationBeforeUpdate": [ "string" ]
     *       },
     *       "UsernameAttributes": [ "string" ],
     *       "UsernameConfiguration": {
     *         "CaseSensitive": boolean
     *       },
     *       "UserPoolAddOns": {
     *         "AdvancedSecurityMode": "string"
     *       },
     *       "UserPoolTags": {
     *         "string" : "string"
     *       },
     *       "VerificationMessageTemplate": {
     *       "DefaultEmailOption": "string",
     *       "EmailMessage": "string",
     *       "EmailMessageByLink": "string",
     *       "EmailSubject": "string",
     *       "EmailSubjectByLink": "string",
     *       "SmsMessage": "string"
     *     }
     *   }
     * }
     * @endcode
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CreateUserPoolResponse {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Name of the user pool
         */
        std::string name;

        /**
         * Convert to a JSON string.
         *
         * @return json string
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
        friend std::ostream &operator<<(std::ostream &os, const CreateUserPoolResponse &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_RESPONSE_H
