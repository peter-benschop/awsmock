//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/CreateEventSourceMappingsResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string CreateEventSourceMappingsResponse::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("User", user);
            rootJson.set("FunctionName", functionName);
            rootJson.set("EventSourceArn", eventSourceArn);
            rootJson.set("BatchSize", batchSize);
            rootJson.set("MaximumBatchingWindowInSeconds", maximumBatchingWindowInSeconds);
            rootJson.set("Enabled", enabled);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void CreateEventSourceMappingsResponse::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("FunctionName", rootObject, functionName);
            Core::JsonUtils::GetJsonValueString("EventSourceArn", rootObject, eventSourceArn);
            Core::JsonUtils::GetJsonValueInt("BatchSize", rootObject, batchSize);
            Core::JsonUtils::GetJsonValueInt("MaximumBatchingWindowInSeconds", rootObject, maximumBatchingWindowInSeconds);
            Core::JsonUtils::GetJsonValueBool("Enabled", rootObject, enabled);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string CreateEventSourceMappingsResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateEventSourceMappingsResponse &r) {
        os << "CreateEventSourceMappingsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
