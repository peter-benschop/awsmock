//
// Created by vogje01 on 4/25/24.
//

#ifndef AWSMOCK_DTO_KMS_DECRYPT_RESPONSE_H
#define AWSMOCK_DTO_KMS_DECRYPT_RESPONSE_H

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
     * Decryption response
     *
     * <p>
     * Ciphertext recipients are not implemented yet.
     * </p>
     *
     * Example:
     * @code{.json}
     * {
     *   "CiphertextForRecipient": blob,
     *   "EncryptionAlgorithm": "string",
     *   "KeyId": "string",
     *   "Plaintext": blob
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct DecryptResponse {

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
         * Plain text.
         *
         * <p>
         * The cipher text is Base64 encoded in case of AWS CLI, plain otherwise.
         * </p>
         */
        std::string plaintext;

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
        friend std::ostream &operator<<(std::ostream &os, const DecryptResponse &r);
    };

}// namespace AwsMock::Dto::KMS

#endif// AWSMOCK_DTO_KMS_DECRYPT_RESPONSE_H
