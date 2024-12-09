//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_LIST_QUEUE_RESPONSE_H
#define AWSMOCK_DTO_SQS_LIST_QUEUE_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/entity/sqs/Queue.h>

namespace AwsMock::Dto::SQS {

    struct ListQueuesResponse {

        /**
         * List of queues
         */
        Database::Entity::SQS::QueueList queueList;

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
         * Convert to JSON representation
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const ListQueuesResponse &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_LIST_QUEUE_RESPONSE_H
