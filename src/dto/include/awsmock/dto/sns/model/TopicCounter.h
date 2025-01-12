//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_TOPIC_COUNTER_H
#define AWSMOCK_DTO_SNS_TOPIC_COUNTER_H

// C++ standard includes
#include <chrono>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::SNS {

    using std::chrono::system_clock;

    struct TopicCounter {

        /**
         * Topic URL
         */
        std::string topicUrl;

        /**
         * Topic ARN
         */
        std::string topicArn;

        /**
         * Topic name
         */
        std::string topicName;

        /**
         * Created
         */
        system_clock::time_point created;

        /**
         * Modified
         */
        system_clock::time_point modified;

        /**
         * Retention period
         */
        long retentionPeriod = 0;

        /**
         * Maximal message size
         */
        long maxMessageSize = 0;

        /**
         * Total number of available message
         */
        long availableMessages = 0;

        /**
         * Total size of all message in the topic
         */
        long size = 0;

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
        friend std::ostream &operator<<(std::ostream &os, const TopicCounter &r);
    };

    typedef std::vector<TopicCounter> TopicCounterList;

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_TOPIC_COUNTER_H
