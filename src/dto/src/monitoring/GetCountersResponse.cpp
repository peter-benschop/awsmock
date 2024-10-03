//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/monitoring/GetCountersResponse.h>

namespace AwsMock::Dto::Monitoring {

    std::string GetCountersResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;

            if (!counters.empty()) {
                Poco::JSON::Array jsonArray;
                for (const auto &counter: counters) {
                    Poco::JSON::Array counterArray;
                    counterArray.add(counter.timestamp.time_since_epoch().count() / 1000000);
                    counterArray.add(counter.performanceValue);
                    jsonArray.add(counterArray);
                }
                rootJson.set("counters", jsonArray);
            }
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.displayText();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetCountersResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetCountersResponse &r) {
        os << "GetCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Monitoring
