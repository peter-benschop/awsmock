//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_SUBSCRIPTIONS_H
#define AWSMOCK_DTO_SNS_SUBSCRIPTIONS_H

// C++ standard includes
#include <sstream>
#include <string>
#include <vector>

namespace AwsMock::Dto::SNS {

    struct Subscription {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Topic ARN
         */
        std::string topicArn;

        /**
         * Protocol
         */
        std::string protocol;

        /**
         * Subscription ARN
         */
        std::string subscriptionArn;

        /**
         * Endpoint
         */
        std::string endpoint;

        /**
         * Owner
         */
        std::string owner;

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
        friend std::ostream &operator<<(std::ostream &os, const Subscription &r);
    };

    typedef std::vector<Subscription> SubscriptionsList;

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_SUBSCRIPTIONS_H
