//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_SUBSCRIBE_REQUEST_H
#define AWSMOCK_DTO_SNS_SUBSCRIBE_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

namespace AwsMock::Dto::SNS {

    struct SubscribeRequest {

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
         * Endpoint
         */
        std::string endpoint;

        /**
         * Owner
         */
        std::string owner;

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
        friend std::ostream &operator<<(std::ostream &os, const SubscribeRequest &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_SUBSCRIBE_REQUEST_H
