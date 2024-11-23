//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sns/ListSubscriptionCountersResponse.h>

namespace AwsMock::Dto::SNS {

    std::string ListSubscriptionCountersResponse::ToJson() const {

        try {
            Poco::JSON::Array queueCounterArrayJson;
            for (const auto &subscriptionCounter: subscriptionCounters) {
                queueCounterArrayJson.add(subscriptionCounter.ToJsonObject());
            }

            Poco::JSON::Object rootJson;
            rootJson.set("SubscriptionCounters", queueCounterArrayJson);
            rootJson.set("Total", total);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListSubscriptionCountersResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListSubscriptionCountersResponse &r) {
        os << "ListSubscriptionCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
