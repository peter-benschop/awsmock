//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_LIST_SUBSCRIPTIONS_BY_TOPIC_RESPONSE_H
#define AWSMOCK_DTO_SNS_LIST_SUBSCRIPTIONS_BY_TOPIC_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Text.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/XML/XMLWriter.h>

// AwsMock includes
#include "awsmock/dto/sns/model/Subscription.h"

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
         * Convert to XML representation
         *
         * @return XML string
         */
        [[nodiscard]] std::string ToXml() const;

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
        friend std::ostream &operator<<(std::ostream &os, const ListSubscriptionsByTopicResponse &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_LIST_SUBSCRIPTIONS_BY_TOPIC_RESPONSE_H
