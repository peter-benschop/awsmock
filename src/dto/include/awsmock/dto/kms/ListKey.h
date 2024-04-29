//
// Created by vogje01 on 4/26/24.
//

#ifndef AWSMOCK_DTO_KMS_LIST_KEY_H
#define AWSMOCK_DTO_KMS_LIST_KEY_H

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
#include <awsmock/dto/kms/KeySpec.h>
#include <awsmock/dto/kms/KeyState.h>
#include <awsmock/dto/kms/KeyUsage.h>

namespace AwsMock::Dto::KMS {

    /**
     * KMS metadata
     *
     * Example:
     * <pre>
     * {
     *   "KeyArn": "string",
     *   "KeyId": "string",
     * }
     * </pre>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListKey {

        /**
         * Key ID
         */
        std::string keyId;

        /**
         * Arn
         */
        std::string keyArn;

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
        friend std::ostream &operator<<(std::ostream &os, const ListKey &r);
    };

}// namespace AwsMock::Dto::KMS

#endif// AWSMOCK_DTO_KMS_LIST_KEY_H
