//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/lambda/EventSourceMapping.h>

namespace AwsMock::Database::Entity::Lambda {

    void EventSourceMapping::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        eventSourceArn = bsoncxx::string::to_string(mResult.value()["eventSourceArn"].get_string().value);
        batchSize = mResult.value()["batchSize"].get_int32().value;
        maximumBatchingWindowInSeconds = mResult.value()["maximumBatchingWindowInSeconds"].get_int32().value;
        enabled = mResult.value()["enabled"].get_bool().value;
        uuid = bsoncxx::string::to_string(mResult.value()["uuid"].get_string().value);
    }

    view_or_value<view, value> EventSourceMapping::ToDocument() const {

        bsoncxx::builder::basic::document eventSourceMappingDoc{};
        eventSourceMappingDoc.append(kvp("eventSourceArn", eventSourceArn));
        eventSourceMappingDoc.append(kvp("batchSize", batchSize));
        eventSourceMappingDoc.append(kvp("maximumBatchingWindowInSeconds", maximumBatchingWindowInSeconds));
        eventSourceMappingDoc.append(kvp("enabled", enabled));
        eventSourceMappingDoc.append(kvp("uuid", uuid));
        return eventSourceMappingDoc.extract();
    }

    Poco::JSON::Object EventSourceMapping::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("eventSourceArn", eventSourceArn);
        jsonObject.set("batchSize", batchSize);
        jsonObject.set("maximumBatchingWindowInSeconds", maximumBatchingWindowInSeconds);
        jsonObject.set("enabled", enabled);

        return jsonObject;
    }

    [[nodiscard]] std::string EventSourceMapping::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const EventSourceMapping &t) {
        os << "EventSourceMapping=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Lambda