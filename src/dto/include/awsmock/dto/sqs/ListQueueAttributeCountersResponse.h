//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_LIST_QUEUE_ATTRIBUTE_COUNTERS_RESPONSE_H
#define AWSMOCK_DTO_SNS_LIST_QUEUE_ATTRIBUTE_COUNTERS_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/sqs/model/AttributeCounter.h>

namespace AwsMock::Dto::SQS {

    struct ListQueueAttributeCountersResponse {

        /**
         * List of attribute counters
         */
        std::vector<AttributeCounter> attributeCounters;

        /**
         * Total number of queues
         */
        long total = 0;

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
        friend std::ostream &operator<<(std::ostream &os, const ListQueueAttributeCountersResponse &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_LIST_QUEUE_ATTRIBUTE_COUNTERS_RESPONSE_H
