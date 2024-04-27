//
// Created by vogje01 on 4/25/24.
//

#ifndef AWSMOCK_DTO_KMS_ENCRYPT_REQUEST_H
#define AWSMOCK_DTO_KMS_ENCRYPT_REQUEST_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/kms/EncryptionAlgorithm.h>

namespace AwsMock::Dto::KMS {

    /**
     * Encryption of supplied blob request
     *
     * Example:
     * <pre>
     * {
     *   "DryRun": boolean,
     *   "EncryptionAlgorithm": "string",
     *   "EncryptionContext": {
     *     "string" : "string"
     *   },
     *   "GrantTokens": [ "string" ],
     *   "KeyId": "string",
     *   "Plaintext": blob
     * }
     * </pre>
     *
     * @author jens.vogt@opitz-consulting.com
     */
    struct EncryptRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Key ID
         */
        std::string keyId;

        /**
         * Encryption algorithm
         */
        EncryptionAlgorithm encryptionAlgorithm;

        /**
         * Grant tokens
         */
        std::vector<std::string> grantTokens;

        /**
         * Dry run
         */
        bool dryRun = false;

        /**
         * Plain text
         *
         * <p>
         * The plain text is Base64 encoded in case of AWS CLI, plain otherwise.
         * </p>
         */
        std::string plainText;

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
        friend std::ostream &operator<<(std::ostream &os, const EncryptRequest &r);
    };

}// namespace AwsMock::Dto::KMS

#endif// AWSMOCK_DTO_KMS_ENCRYPT_REQUEST_H
