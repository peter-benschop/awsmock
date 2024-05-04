//
// Created by vogje01 on 4/25/24.
//

#ifndef AWSMOCK_DTO_KMS_LIST_KEYS_REQUEST_H
#define AWSMOCK_DTO_KMS_LIST_KEYS_REQUEST_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include "awsmock/dto/kms/model/KeySpec.h"
#include "awsmock/dto/kms/model/KeyUsage.h"
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::KMS {

    /**
     * List all KMS keys request
     *
     * Example:
     * @code{.json}
     * {
     *   "Limit": number,
     *   "Marker": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListKeysRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Marker for paging
         */
        std::string marker;

        /**
         * Limit
         */
        long limit;

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
        friend std::ostream &operator<<(std::ostream &os, const ListKeysRequest &r);
    };

}// namespace AwsMock::Dto::KMS

#endif// AWSMOCK_DTO_KMS_LIST_KEYS_REQUEST_H
