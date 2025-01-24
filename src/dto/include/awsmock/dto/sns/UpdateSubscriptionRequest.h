//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_UPDATE_SUBSCRIPTION_REQUEST_H
#define AWSMOCK_DTO_SNS_UPDATE_SUBSCRIPTION_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// Awsmock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/StringUtils.h>

namespace AwsMock::Dto::SNS {

    struct UpdateSubscriptionRequest {

        /**
         * Topic ARN
         */
        std::string topicArn;

        /**
         * Subscription ARN
         */
        std::string subscriptionArn;

        /**
         * Protocol
         */
        std::string protocol;

        /**
         * Endpoint
         */
        std::string endpoint;

        /**
         * Owner
         */
        std::string owner;

        /**
         * @brief Convert from JSON representation
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * @brief Convert to JSON representation
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const UpdateSubscriptionRequest &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_UPDATE_SUBSCRIPTION_REQUEST_H
