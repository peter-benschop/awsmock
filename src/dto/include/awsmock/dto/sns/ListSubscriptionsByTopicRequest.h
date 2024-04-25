//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_LIST_SUBSCRIPTIONS_BY_TOPI_ARN_REQUEST_H
#define AWSMOCK_DTO_SNS_LIST_SUBSCRIPTIONS_BY_TOPI_ARN_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

namespace AwsMock::Dto::SNS {

    struct ListSubscriptionsByTopicRequest {

        /**
     * AWS region
     */
        std::string region;

        /**
     * Topic ARN
     */
        std::string topicArn;

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
        friend std::ostream &operator<<(std::ostream &os, const ListSubscriptionsByTopicRequest &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_LIST_SUBSCRIPTIONS_BY_TOPI_ARN_REQUEST_H
