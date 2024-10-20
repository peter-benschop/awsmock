//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_TOPIC_COUNTER_H
#define AWSMOCK_DTO_SNS_TOPIC_COUNTER_H

// C++ standard includes
#include <chrono>
#include <sstream>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>

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
         * Number of message available
         */
        long available;

        /**
         * Retention period
         */
        long retentionPeriod;

        /**
         * Maximal message size
         */
        long maxMessageSize;

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
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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

#endif// AWSMOCK_DTO_SQS_QUEUEATTRIBUTE_H
