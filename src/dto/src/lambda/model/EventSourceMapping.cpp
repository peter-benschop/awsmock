//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/model/EventSourceMapping.h>

namespace AwsMock::Dto::Lambda {

    view_or_value<view, value> EventSourceMapping::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "User", user);
            Core::Bson::BsonUtils::SetStringValue(document, "FunctionArn", functionArn);
            Core::Bson::BsonUtils::SetStringValue(document, "EventSourceArn", eventSourceArn);
            Core::Bson::BsonUtils::SetIntValue(document, "BatchSize", batchSize);
            Core::Bson::BsonUtils::SetIntValue(document, "MaximumBatchingWindowInSeconds", maximumBatchingWindowInSeconds);
            Core::Bson::BsonUtils::SetStringValue(document, "UUID", uuid);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string EventSourceMapping::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
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
