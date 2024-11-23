//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueCountersResponse.h>

namespace AwsMock::Dto::SQS {

    std::string ListTopicCountersResponse::ToJson() const {

        try {
            Poco::JSON::Array queueCounterArrayJson;
            for (const auto &queueCounter: queueCounters) {
                queueCounterArrayJson.add(queueCounter.ToJsonObject());
            }

            Poco::JSON::Object rootJson;
            rootJson.set("QueueCounters", queueCounterArrayJson);
            rootJson.set("Total", total);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListTopicCountersResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListTopicCountersResponse &r) {
        os << "ListQueueCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
