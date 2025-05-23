//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_LIST_QUEUE_ATTRIBUTE_COUNTERS_RESPONSE_H
#define AWSMOCK_DTO_SNS_LIST_QUEUE_ATTRIBUTE_COUNTERS_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/common/BaseCounter.h>
#include <awsmock/dto/sqs/model/AttributeCounter.h>

namespace AwsMock::Dto::SQS {

    struct ListQueueAttributeCountersResponse final : Common::BaseCounter<ListQueueAttributeCountersResponse> {

        /**
         * List of attribute counters
         */
        std::vector<AttributeCounter> attributeCounters;

        /**
         * Total number of queues
         */
        long total = 0;

      private:

        friend ListQueueAttributeCountersResponse tag_invoke(boost::json::value_to_tag<ListQueueAttributeCountersResponse>, boost::json::value const &v) {
            ListQueueAttributeCountersResponse r;
            r.total = v.at("total").as_int64();
            r.attributeCounters = boost::json::value_to<std::vector<AttributeCounter>>(v.at("messages"));
            return r;
        }

        friend void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, ListQueueAttributeCountersResponse const &obj) {
            jv = {
                    {"region", obj.region},
                    {"user", obj.user},
                    {"requestId", obj.requestId},
                    {"total", obj.total},
                    {"messageCounters", boost::json::value_from(obj.attributeCounters)},
            };
        }
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SNS_LIST_QUEUE_ATTRIBUTE_COUNTERS_RESPONSE_H
