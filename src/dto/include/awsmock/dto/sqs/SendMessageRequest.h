//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_SEND_MESSAGE_REQUEST_H
#define AWSMOCK_DTO_SQS_SEND_MESSAGE_REQUEST_H

// C++ standard includes
#include <string>

// Poco includes
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/dto/sqs/MessageAttribute.h>
#include <awsmock/dto/sqs/SqsCommonRequest.h>

namespace AwsMock::Dto::SQS {

    struct SendMessageRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Queue URL
         */
        std::string queueUrl;

        /**
         * Queue ARN
         */
        std::string queueArn;

        /**
         * Queue name
         */
        std::string queueName;

        /**
         * Message body
         */
        std::string body;

        /**
         * Message userAttributes
         */
        MessageAttributeList attributes;

        /**
         * Message ID
         */
        std::string messageId;

        /**
         * Request ID
         */
        std::string requestId;

        /**
         * Converts the JSON string to a DTO
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

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
        friend std::ostream &operator<<(std::ostream &os, const SendMessageRequest &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_SEND_MESSAGE_REQUEST_H
