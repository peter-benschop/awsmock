//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_CREATE_TOPIC_REQUEST_H
#define AWSMOCK_DTO_SNS_CREATE_TOPIC_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

namespace AwsMock::Dto::SNS {

    struct CreateTopicRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Name
         */
        std::string topicName;

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
        friend std::ostream &operator<<(std::ostream &os, const CreateTopicRequest &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_CREATE_TOPIC_REQUEST_H
