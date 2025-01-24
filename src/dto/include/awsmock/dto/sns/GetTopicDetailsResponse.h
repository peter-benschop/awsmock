//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_GET_TOPIC_DETAILS_RESPONSE_H
#define AWSMOCK_DTO_SQS_GET_TOPIC_DETAILS_RESPONSE_H

// C++ standard includes
#include <chrono>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/ServiceException.h>

namespace AwsMock::Dto::SNS {

    using std::chrono::system_clock;

    /**
     * @brief Get topic details response.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct GetTopicDetailsResponse {

        /**
         * Region
         */
        std::string region;

        /**
         * Topic name
         */
        std::string topicName;

        /**
         * Topic URL
         */
        std::string topicUrl;

        /**
         * Topic ARN
         */
        std::string topicArn;

        /**
         * Number of messages
         */
        long messageCount;

        /**
         * Size of all messages
         */
        long size;

        /**
         * Topic owner
         */
        std::string owner;

        /**
         * Created timestamp
         */
        system_clock::time_point created;

        /**
         * Modified timestamp
         */
        system_clock::time_point modified;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const GetTopicDetailsResponse &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SQS_GET_TOPIC_DETAILS_RESPONSE_H
