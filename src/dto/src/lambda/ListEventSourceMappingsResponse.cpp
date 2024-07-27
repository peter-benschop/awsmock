//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/ListEventSourceMappingsResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string ListEventSourceMappingsResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            Poco::JSON::Array jsonMappingArray;
            for (const auto &eventSourceMapping: eventSourceMappings) {
                jsonMappingArray.add(eventSourceMapping.ToJsonObject());
            }
            rootJson.set("EventSourceMappings", jsonMappingArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListEventSourceMappingsResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListEventSourceMappingsResponse &r) {
        os << "ListEventSourceMappingsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
