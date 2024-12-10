//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_LIST_QUEUES_REQUEST_H
#define AWSMOCK_DTO_SQS_LIST_QUEUES_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/entity/sqs/Queue.h>

namespace AwsMock::Dto::SQS {

    /**
     *
     * Example
     * @code(.json)
     * {
     *   "MaxResults":10,
     *   "NextToken":"",
     *   "QueueNamePrefix":""
     * }"
     * @endcode
     *
     */
    struct ListQueuesRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Max results
         */
        int maxResults = -1;

        /**
         * Next token
         */
        std::string nextToken;

        /**
         * Queue name prefix
         */
        std::string queueNamePrefix;

        /**
         * Convert to JSON representation
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

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
        friend std::ostream &operator<<(std::ostream &os, const ListQueuesRequest &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_LIST_QUEUES_REQUEST_H
