//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/lambda/GetFunctionCountersResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string GetFunctionCountersResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;

            rootJson.set("region", region);
            rootJson.set("functionName", functionName);
            rootJson.set("user", user);
            rootJson.set("handler", handler);
            rootJson.set("user", user);
            rootJson.set("role", role);
            rootJson.set("size", size);
            rootJson.set("concurrency", concurrency);
            rootJson.set("runtime", runtime);
            rootJson.set("invocations", invocations);
            rootJson.set("averageRuntime", averageRuntime);
            rootJson.set("lastInvocation", Core::DateTimeUtils::ToISO8601(lastInvocation));
            rootJson.set("created", Core::DateTimeUtils::ToISO8601(created));
            rootJson.set("modified", Core::DateTimeUtils::ToISO8601(modified));

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetFunctionCountersResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetFunctionCountersResponse &r) {
        os << "GetFunctionCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda
