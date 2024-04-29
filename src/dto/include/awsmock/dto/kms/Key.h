//
// Created by vogje01 on 4/26/24.
//

#ifndef AWSMOCK_DTO_KMS_KEY_H
#define AWSMOCK_DTO_KMS_KEY_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/kms/EncryptionAlgorithm.h>
#include <awsmock/dto/kms/KeySpec.h>
#include <awsmock/dto/kms/KeyState.h>
#include <awsmock/dto/kms/KeyUsage.h>
#include <awsmock/dto/kms/Origin.h>

namespace AwsMock::Dto::KMS {

    /**
     * KMS metadata
     *
     * Example:
     * <pre>
     *   "Arn": "string",
     *   "AWSAccountId": "string",
     *   "CloudHsmClusterId": "string",
     *   "CreationDate": number,
     *   "CustomerMasterKeySpec": "string",
     *   "CustomKeyStoreId": "string",
     *   "DeletionDate": number,
     *   "Description": "string",
     *   "Enabled": boolean,
     *   "EncryptionAlgorithms": [ "string" ],
     *   "ExpirationModel": "string",
     *   "KeyId": "string",
     *   "KeyManager": "string",
     *   "KeySpec": "string",
     *   "KeyState": "string",
     *   "KeyUsage": "string",
     *   "MacAlgorithms": [ "string" ],
     *   "MultiRegion": boolean,
     *   "MultiRegionConfiguration": {
     *     "MultiRegionKeyType": "string",
     *     "PrimaryKey": {
     *       "Arn": "string",
     *       "Region": "string"
     *     },
     *     "ReplicaKeys": [
     *       {
     *         "Arn": "string",
     *         "Region": "string"
     *       }
     *     ]
     *   },
     *   "Origin": "string",
     *   "PendingDeletionWindowInDays": number,
     *   "SigningAlgorithms": [ "string" ],
     *   "ValidTo": number,
     *   "XksKeyConfiguration": {
     *     "Id": "string"
     *   }
     * }
     * </pre>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Key {

        /**
         * Key ID
         */
        std::string keyId;

        /**
         * Arn
         */
        std::string arn;

        /**
         * Key specification
         */
        KeySpec keySpec;

        /**
         * Key usage
         */
        KeyUsage keyUsage;

        /**
         * Key state
         */
        KeyState keyState;

        /**
         * Multi region
         */
        bool multiRegion;

        /**
         * Description
         */
        std::string description;

        /**
         * Creation date
         */
        long creationDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        /**
         * Deletion date
         */
        long deletionDate = 0;

        /**
         * Enabled flag
         */
        bool enabled;

        /**
         * Origin
         */
        Origin origin;

        /**
         * Encryption algorithms
         */
        std::vector<Dto::KMS::EncryptionAlgorithm> encryptionAlgorithms;

        /**
         * Convert to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Convert from JSON representation
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

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
        friend std::ostream &operator<<(std::ostream &os, const Key &r);
    };

}// namespace AwsMock::Dto::KMS

#endif// AWSMOCK_DTO_KMS_KEY_H
