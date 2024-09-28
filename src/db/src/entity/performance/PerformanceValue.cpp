//
// Created by vogje01 on 01/06/2023.
//

#include "awsmock/entity/performance/PerformanceValue.h"

namespace AwsMock::Database::Entity::Performance {

    view_or_value<view, value> PerformanceValue::ToDocument() const {

        try {
            bsoncxx::builder::basic::document keyDoc;
            keyDoc.append(
                    kvp("key", key),
                    kvp("value", perfValue),
                    kvp("created", bsoncxx::types::b_date(created)));
            return keyDoc.extract();

        } catch (mongocxx::exception &e) {
            log_error << e.what();
            throw Core::DatabaseException(e.what());
        }
    }

    void PerformanceValue::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        try {
            oid = mResult.value()["_id"].get_oid().value.to_string();
            key = bsoncxx::string::to_string(mResult.value()["key"].get_string().value);
            perfValue = mResult.value()["value"].get_double().value;
            created = mResult.value()["created"].get_date();

        } catch (mongocxx::exception &e) {
            log_error << e.what();
            throw Core::DatabaseException(e.what());
        }
    }

    Poco::JSON::Object PerformanceValue::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("key", key);
        jsonObject.set("value", perfValue);
        jsonObject.set("created", Core::DateTimeUtils::ISO8601(created));

        return jsonObject;
    }

    std::string PerformanceValue::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PerformanceValue &t) {
        os << "PerformanceValue=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::Performance
