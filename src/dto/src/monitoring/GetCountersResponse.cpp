//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/monitoring/GetCountersResponse.h>

namespace AwsMock::Dto::Monitoring {

    std::string GetCountersResponse::ToJson() const {

        try {

            document rootDocument;
            if (!counters.empty()) {
                array jsonArray;
                for (const auto &counter: counters) {
                    array jsonElement;
                    jsonElement.append(Core::DateTimeUtils::ToISO8601(counter.timestamp));
                    jsonElement.append(counter.performanceValue);
                    jsonArray.append(jsonElement);
                }
                rootDocument.append(kvp("counters", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (Poco::Exception &exc) {
            log_error << exc.displayText();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetCountersResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetCountersResponse &r) {
        os << "GetCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Monitoring
