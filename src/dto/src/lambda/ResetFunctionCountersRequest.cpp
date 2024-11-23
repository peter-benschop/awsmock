//
// Created by vogje01 on 31/05/2023.
//

#include <awsmock/dto/lambda/ResetFunctionCountersRequest.h>

namespace AwsMock::Dto::Lambda {

    void ResetFunctionCountersRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            if (!rootObject->get("region").isEmpty()) {
                region = rootObject->get("region").convert<std::string>();
            }
            if (!rootObject->get("functionName").isEmpty()) {
                functionName = rootObject->get("functionName").convert<std::string>();
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ResetFunctionCountersRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("functionName", functionName);
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ResetFunctionCountersRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ResetFunctionCountersRequest &r) {
        os << "ResetFunctionCountersRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
