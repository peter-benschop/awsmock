//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/ListEventSourceMappingsRequest.h>

namespace AwsMock::Dto::Lambda {

    std::string ListEventSourceMappingsRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("User", user);
            rootJson.set("FunctionName", functionName);
            rootJson.set("EventSourceArn", eventSourceArn);
            rootJson.set("Marker", marker);
            rootJson.set("MaxItems", maxItems);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void ListEventSourceMappingsRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("FunctionName", rootObject, functionName);
            Core::JsonUtils::GetJsonValueString("EventSourceArn", rootObject, eventSourceArn);
            Core::JsonUtils::GetJsonValueString("Marker", rootObject, marker);
            Core::JsonUtils::GetJsonValueInt("MaxItems", rootObject, maxItems);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListEventSourceMappingsRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListEventSourceMappingsRequest &r) {
        os << "ListEventSourceMappingsRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
