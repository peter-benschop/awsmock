//
// Created by vogje01 on 4/25/24.
//

#ifndef AWSMOCK_DTO_KMS_DECRYPT_REQUEST_H
#define AWSMOCK_DTO_KMS_DECRYPT_REQUEST_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include "awsmock/dto/kms/model/EncryptionAlgorithm.h"
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::KMS {

    /**
     * Decryption request
     *
     * <p>
     * Recipients are not implemented yet.
     * </p>
     *
     * Example:
     * @code{.json}
     * {
     *   "CiphertextBlob": blob,
     *   "DryRun": boolean,
     *   "EncryptionAlgorithm": "string",
     *   "EncryptionContext": {
     *     "string" : "string"
     *   },
     *   "GrantTokens": [ "string" ],
     *   "KeyId": "string",
     *   "Recipient": {
     *     "AttestationDocument": blob,
     *     "KeyEncryptionAlgorithm": "string"
     *   }
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct DecryptRequest {

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
         * Encryption model
         */
        std::map<std::string, std::string> encryptionContext;

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
        std::string ciphertext;

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
        friend std::ostream &operator<<(std::ostream &os, const DecryptRequest &r);
    };

}// namespace AwsMock::Dto::KMS

#endif// AWSMOCK_DTO_KMS_DECRYPT_REQUEST_H
