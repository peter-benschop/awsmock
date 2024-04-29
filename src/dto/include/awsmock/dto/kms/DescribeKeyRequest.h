//
// Created by vogje01 on 4/25/24.
//

#ifndef AWSMOCK_DTO_KMS_DESCRIBE_KEY_REQUEST_H
#define AWSMOCK_DTO_KMS_DESCRIBE_KEY_REQUEST_H

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
     *   "GrantTokens": [ "string" ],
     *   "KeyId": "string"
     * }
     * </pre>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct DescribeKeyRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Key ID
         */
        std::string keyId;

        /**
         * Grant token
         */
        std::vector<std::string> grantTokens;

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
        friend std::ostream &operator<<(std::ostream &os, const DescribeKeyRequest &r);
    };

}// namespace AwsMock::Dto::KMS

#endif// AWSMOCK_DTO_KMS_DESCRIBE_KEY_REQUEST_H
