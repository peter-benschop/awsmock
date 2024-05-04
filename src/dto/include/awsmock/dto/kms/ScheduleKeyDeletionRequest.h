//
// Created by vogje01 on 4/25/24.
//

#ifndef AWSMOCK_DTO_KMS_SCHEDULE_KEX_DELETION_REQUEST_H
#define AWSMOCK_DTO_KMS_SCHEDULE_KEX_DELETION_REQUEST_H

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
     * Schedule a KMS key deletion
     *
     * Example:
     * @code{.json}
     * {
     *   "KeyId": "string",
     *   "PendingWindowInDays": number
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ScheduleKeyDeletionRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Key ID
         */
        std::string keyId;

        /**
         * Pending window in days
         */
        int pendingWindowInDays = 30;

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
        friend std::ostream &operator<<(std::ostream &os, const ScheduleKeyDeletionRequest &r);
    };

}// namespace AwsMock::Dto::KMS

#endif// AWSMOCK_DTO_KMS_SCHEDULE_KEX_DELETION_REQUEST_H
