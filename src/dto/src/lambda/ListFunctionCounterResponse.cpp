
#include <awsmock/dto/lambda/ListFunctionCountersResponse.h>

namespace AwsMock::Dto::Lambda {

    std::string ListFunctionCountersResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("total", total);

            // Contents
            if (!functionCounters.empty()) {

                Poco::JSON::Array jsonBucketArray;
                for (auto &functionCounter: functionCounters) {
                    Poco::JSON::Object jsonObject;
                    jsonObject.set("functionName", functionCounter.functionName);
                    jsonObject.set("runtime", functionCounter.runtime);
                    jsonObject.set("handler", functionCounter.handler);
                    jsonObject.set("averageRuntime", functionCounter.averageRuntime);
                    jsonObject.set("invocations", functionCounter.invocations);
                    jsonBucketArray.add(jsonObject);
                }

                rootJson.set("functionCounters", jsonBucketArray);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string ListFunctionCountersResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListFunctionCountersResponse &r) {
        os << "ListFunctionCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Lambda