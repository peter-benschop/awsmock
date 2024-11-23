//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sns/ListTopicCountersResponse.h>

namespace AwsMock::Dto::SNS {

    std::string ListTopicCountersResponse::ToJson() const {

        try {
            Poco::JSON::Array queueCounterArrayJson;
            for (const auto &topicCounter: topicCounters) {
                queueCounterArrayJson.add(topicCounter.ToJsonObject());
            }

            Poco::JSON::Object rootJson;
            rootJson.set("TopicCounters", queueCounterArrayJson);
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
        os << "ListTopicCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
