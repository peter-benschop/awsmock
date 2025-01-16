//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_DTO_SQS_EVENT_NOTIFICATION_H
#define AWSMOCK_DTO_SQS_EVENT_NOTIFICATION_H

// C++ standard includes
#include <string>
#include <vector>

// Boost includes
#include <boost/regex/v5/regex.hpp>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/sqs/model/EventRecord.h>

namespace AwsMock::Dto::SQS {

    /**
     * @brief SQS event notification
     *
     * @code(.json)
     * {
     *   "Records": [
     *     {
     *       "messageId": "059f36b4-87a3-44ab-83d2-661975830a7d",
     *       "receiptHandle": "AQEBwJnKyrHigUMZj6rYigCgxlaS3SLy0a...",
     *       "body": "Test message.",
     *       "attributes": {
     *         "ApproximateReceiveCount": "1",
     *         "SentTimestamp": "1545082649183",
     *         "SenderId": "AIDAIENQZJOLO23YVJ4VO",
     *         "ApproximateFirstReceiveTimestamp": "1545082649185"
     *       },
     *       "messageAttributes": {},
     *       "md5OfBody": "e4e68fb7bd0e697a0ae8f1bb342846b3",
     *       "eventSource": "aws:sqs",
     *       "eventSourceARN": "arn:aws:sqs:us-east-2:123456789012:my-queue",
     *       "awsRegion": "us-east-2"
     *     }
     *   ]
     * }
     * @endcode
     */
    struct EventNotification {

        /**
         * S3 event record
         */
        std::vector<Record> records;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts a JSON representation to s DTO.
         *
         * @param jsonString JSON string.
         */
        void FromJson(const std::string &jsonString);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const EventNotification &e);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_EVENT_NOTIFICATION_H
