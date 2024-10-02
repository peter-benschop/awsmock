//
// Created by vogje01 on 10/2/24.
//
#include "awsmock/core/DateTimeUtils.h"
#include <awsmock/entity/monitoring/Counter.h>

namespace AwsMock::Database::Entity::Monitoring {

    view_or_value<view, value> Counter::ToDocument() const {

        view_or_value<view, value> counterDoc = make_document(
                kvp("name", name),
                kvp("labelName", labelName),
                kvp("labelValue", labelValue),
                kvp("value", performanceValue),
                kvp("timestamp", bsoncxx::types::b_date(timestamp)));
        return counterDoc;
    }

    void Counter::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
        labelName = bsoncxx::string::to_string(mResult.value()["labelName"].get_string().value);
        labelValue = bsoncxx::string::to_string(mResult.value()["labelValue"].get_string().value);
        performanceValue = mResult.value()["value"].get_double().value;
        timestamp = bsoncxx::types::b_date(mResult.value()["timestamp"].get_date().value);
    }

    Poco::JSON::Object Counter::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("name", name);
        jsonObject.set("labelName", labelName);
        jsonObject.set("labelValue", labelValue);
        jsonObject.set("value", performanceValue);
        jsonObject.set("timestamp", Core::DateTimeUtils::ISO8601(timestamp));
        return jsonObject;
    }

    std::string Counter::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Counter &counter) {
        os << "Counter=" << bsoncxx::to_json(counter.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::Monitoring