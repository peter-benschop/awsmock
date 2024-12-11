//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/ListEventSourceMappingsResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string ListEventSourceMappingsResponse::ToJson() const {

        try {

            document document;
            if (!eventSourceMappings.empty()) {
                array jsonArray;
                for (const auto &eventSourceMapping: eventSourceMappings) {
                    jsonArray.append(eventSourceMapping.ToDocument());
                }
                document.append(kvp("EventSourceMappings", jsonArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListEventSourceMappingsResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListEventSourceMappingsResponse &r) {
        os << "ListEventSourceMappingsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
