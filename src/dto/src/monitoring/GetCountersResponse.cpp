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
                    jsonArray.add(counter.ToJsonObject());
                }
                rootJson.set("counters", jsonArray);
            }
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
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
