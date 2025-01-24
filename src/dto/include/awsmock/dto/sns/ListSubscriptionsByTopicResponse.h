//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_LIST_SUBSCRIPTIONS_BY_TOPIC_RESPONSE_H
#define AWSMOCK_DTO_SNS_LIST_SUBSCRIPTIONS_BY_TOPIC_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/dto/sns/model/Subscription.h>

namespace AwsMock::Dto::SNS {

    struct ListSubscriptionsByTopicResponse {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Topic ARN
         */
        std::string topicArn;

        /**
         * Subscriptions
         */
        SubscriptionsList subscriptions;

        /**
         * Next token
         */
        std::string nextToken;

        /**
         * Total number of queue
         */
        long total;

        /**
         * @brief Convert to JSON representation
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert to XML representation
         *
         * @return XML string
         */
        [[nodiscard]] std::string ToXml() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const ListSubscriptionsByTopicResponse &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_LIST_SUBSCRIPTIONS_BY_TOPIC_RESPONSE_H
