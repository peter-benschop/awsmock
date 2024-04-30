//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_SUBSCRIBEREQUEST_H
#define AWSMOCK_DTO_SNS_SUBSCRIBEREQUEST_H

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
        friend std::ostream &operator<<(std::ostream &os, const SubscribeRequest &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_SUBSCRIBEREQUEST_H
