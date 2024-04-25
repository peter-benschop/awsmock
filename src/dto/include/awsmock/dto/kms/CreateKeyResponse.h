//
// Created by vogje01 on 4/25/24.
//

#ifndef AWSMOCK_DTO_KMS_CREATE_KEY_RESPONSE_H
#define AWSMOCK_DTO_KMS_CREATE_KEY_RESPONSE_H

// C++ standard includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/kms/CustomerMasterKeySpec.h>

namespace AwsMock::Dto::Kms {

    /**
     * Create KMS key response
     *
     * Example:
     * <pre>
     * {
     *   "KeyMetadata": {
     *      "Arn": "string",
     *      "AWSAccountId": "string",
     *      "CloudHsmClusterId": "string",
     *      "CreationDate": number,
     *      "CustomerMasterKeySpec": "string",
     *      "CustomKeyStoreId": "string",
     *      "DeletionDate": number,
     *      "Description": "string",
     *      "Enabled": boolean,
     *      "EncryptionAlgorithms": [ "string" ],
     *      "ExpirationModel": "string",
     *      "KeyId": "string",
     *      "KeyManager": "string",
     *      "KeySpec": "string",
     *      "KeyState": "string",
     *      "KeyUsage": "string",
     *      "MacAlgorithms": [ "string" ],
     *      "MultiRegion": boolean,
     *      "MultiRegionConfiguration": {
     *         "MultiRegionKeyType": "string",
     *         "PrimaryKey": {
     *            "Arn": "string",
     *            "Region": "string"
     *         },
     *         "ReplicaKeys": [
     *           {
     *             "Arn": "string",
     *             "Region": "string"
     *           }
     *         ]
     *      },
     *      "Origin": "string",
     *      "PendingDeletionWindowInDays": number,
     *      "SigningAlgorithms": [ "string" ],
     *      "ValidTo": number,
     *      "XksKeyConfiguration": {
     *         "Id": "string"
     *      }
     *    }
     * }
     * </pre>
     *
     * @author jens.vogt@opitz-consulting.com
     */
    struct CreateKeyResponse {

        /**
         * Customer master key specification
         */
        CustomerMasterKeySpec customerMasterKeySpec = CustomerMasterKeySpec::SYMMETRIC_DEFAULT;

        /**
         * Customer key store ID
         */
        std::string customKeyStoreId;

        /**
         * Description
         */
        std::string description;

        /**
         * Key specification
         */
        std::string keySpec;

        /**
         * Key usage
         */
        std::string keyUsage;

        /**
         * Multi region
         */
        bool multiRegion = false;

        /**
         * Bypass policy lockout safety check
         */
        bool bypassPolicyLockoutSafetyCheck = false;

        /**
         * Origin
         */
        std::string origin;

        /**
         * Policy
         */
        std::string policy;

        /**
         * Converts the JSON string to DTO.
         *
         * @param jsonString JSON string
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
         * @return DTO as JSON string.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const CreateKeyResponse &r);
    };

}// namespace AwsMock::Dto::Kms

#endif// AWSMOCK_DTO_KMS_CREATE_KEY_RESPONSE_H
