//
// Created by vogje01 on 4/25/24.
//

#ifndef AWSMOCK_DTO_KMS_SCHEDULE_KEY_DELETION_RESPONSE_H
#define AWSMOCK_DTO_KMS_SCHEDULE_KEY_DELETION_RESPONSE_H

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
#include <awsmock/dto/kms/Key.h>
#include <awsmock/dto/kms/KeySpec.h>

namespace AwsMock::Dto::KMS {

    /**
     * Create KMS key response
     *
     * Example:
     * <pre>
     * {
     *   "DeletionDate": number,
     *   "KeyId": "string",
     *   "KeyState": "string",
     *   "PendingWindowInDays": number
     * }
     * </pre>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ScheduledKeyDeletionResponse {

        /**
         * Deletion date as timestamp
         */
        std::string keyId;

        /**
         * Key state
         */
        std::string keyState;

        /**
         * Deletion date as timestamp
         */
        long deletionDate;

        /**
         * Pending window in days
         */
        int pendingWindowInDays;

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
        friend std::ostream &operator<<(std::ostream &os, const ScheduledKeyDeletionResponse &r);
    };

}// namespace AwsMock::Dto::KMS

#endif// AWSMOCK_DTO_KMS_SCHEDULE_KEY_DELETION_RESPONSE_H
