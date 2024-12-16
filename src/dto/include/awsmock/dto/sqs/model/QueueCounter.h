//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_QUEUE_COUNTER_H
#define AWSMOCK_DTO_SQS_QUEUE_COUNTER_H

// C++ standard includes
#include <chrono>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::SQS {

    using std::chrono::system_clock;

    struct QueueCounter {

        /**
         * Queue URL
         */
        std::string queueUrl;

        /**
         * Queue ARN
         */
        std::string queueArn;

        /**
         * Queue name
         */
        std::string queueName;

        /**
         * Created
         */
        system_clock::time_point created;

        /**
         * Modified
         */
        system_clock::time_point modified;

        /**
         * Number of message available
         */
        long available;

        /**
         * Number of message invisible
         */
        long invisible;

        /**
         * Number of message delayed
         */
        long delayed;

        /**
         * Visibility timeout
         */
        int visibilityTimeout;

        /**
         * Message delay
         */
        int delay;

        /**
         * Retention period
         */
        long retentionPeriod;

        /**
         * Maximal message size
         */
        long maxMessageSize;

        /**
         * Total size of message in the queue
         */
        long size;

        /**
         * Is DQL
         */
        bool isDlq;

        /**
         * @brief Converts the DTO to a JSON string.
         *
         * @return DTO as JSON string.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

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
        friend std::ostream &operator<<(std::ostream &os, const QueueCounter &r);
    };

    typedef std::vector<QueueCounter> QueueCounterList;

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_QUEUEATTRIBUTE_H
