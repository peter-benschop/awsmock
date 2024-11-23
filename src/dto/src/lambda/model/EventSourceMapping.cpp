//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/model/EventSourceMapping.h>

namespace AwsMock::Dto::Lambda {

    Poco::JSON::Object EventSourceMapping::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("User", user);
            rootJson.set("FunctionArn", functionArn);
            rootJson.set("EventSourceArn", eventSourceArn);
            rootJson.set("BatchSize", batchSize);
            rootJson.set("MaximumBatchingWindowInSeconds", maximumBatchingWindowInSeconds);
            rootJson.set("UUID", uuid);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string EventSourceMapping::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string EventSourceMapping::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const EventSourceMapping &f) {
        os << "EventSourceMapping=" << f.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Lambda
