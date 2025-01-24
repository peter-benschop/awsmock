//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_PUBLISH_REQUEST_H
#define AWSMOCK_DTO_SNS_PUBLISH_REQUEST_H

// C++ standard includes
#include "model/MessageAttribute.h"


#include <map>
#include <sstream>
#include <string>

namespace AwsMock::Dto::SNS {

    struct PublishRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Topic ARN
         */
        std::string topicArn;

        /**
         * Target ARN
         */
        std::string targetArn;

        /**
         * Message body
         */
        std::string message;

        /**
         * MessageAttributes
         */
        std::map<std::string, MessageAttribute> messageAttributes;

        /**
         * Request ID
         */
        std::string requestId;

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
        friend std::ostream &operator<<(std::ostream &os, const PublishRequest &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_PUBLISH_REQUEST_H
