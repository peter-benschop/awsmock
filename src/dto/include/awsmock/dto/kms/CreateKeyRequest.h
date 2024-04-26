//
// Created by vogje01 on 4/25/24.
//

#ifndef AWSMOCK_DTO_KMS_CREATE_KEY_REQUEST_H
#define AWSMOCK_DTO_KMS_CREATE_KEY_REQUEST_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/kms/KeySpec.h>
#include <awsmock/dto/kms/KeyUsage.h>

namespace AwsMock::Dto::KMS {

    /**
     * Create KMS key request
     *
     * Example:
     * <pre>
     * {
     *   "BypassPolicyLockoutSafetyCheck": boolean,
     *   "KeySpec": "string",
     *   "CustomKeyStoreId": "string",
     *   "Description": "string",
     *   "KeySpec": "string",
     *   "KeyUsage": "string",
     *   "MultiRegion": boolean,
     *   "Origin": "string",
     *   "Policy": "string",
     *   "Tags": [
     *     {
     *       "TagKey": "string",
     *       "TagValue": "string"
     *     }
     *   ],
     *   "XksKeyId": "string"
     * }
     * </pre>
     *
     * @author jens.vogt@opitz-consulting.com
     */
    struct CreateKeyRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Customer master key specification
         */
        KeySpec customerMasterKeySpec = KeySpec::SYMMETRIC_DEFAULT;

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
        KeyUsage keyUsage;

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
        friend std::ostream &operator<<(std::ostream &os, const CreateKeyRequest &r);
    };

}// namespace AwsMock::Dto::KMS

#endif// AWSMOCK_DTO_KMS_CREATE_KEY_REQUEST_H
