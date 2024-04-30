//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/entity/s3/QueueNotification.h>

namespace AwsMock::Database::Entity::S3 {

    bool QueueNotification::CheckFilter(const std::string &key) {

        if (filterRules.empty()) {
            return true;
        }

        return std::ranges::any_of(filterRules, [key](const FilterRule &rule) {
            return (rule.name == "prefix" && key.starts_with(rule.value)) || (rule.name == "suffix" && key.ends_with(rule.value));
        });
    }

    view_or_value<view, value> QueueNotification::ToDocument() const {

        auto queueNotificationDoc = bsoncxx::builder::basic::document{};
        queueNotificationDoc.append(kvp("id", id));
        queueNotificationDoc.append(kvp("queueArn", queueArn));

        // Events
        auto eventsDoc = bsoncxx::builder::basic::array{};
        for (const auto &event: events) {
            eventsDoc.append(event);
        }
        queueNotificationDoc.append(kvp("events", eventsDoc));

        auto filterRulesDoc = bsoncxx::builder::basic::array{};
        for (const auto &filterRule: filterRules) {
            filterRulesDoc.append(filterRule.ToDocument());
        }
        queueNotificationDoc.append(kvp("filterRules", filterRulesDoc));

        return queueNotificationDoc.extract();
    }

    QueueNotification QueueNotification::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        try {

            id = bsoncxx::string::to_string(mResult.value()["id"].get_string().value);
            queueArn = bsoncxx::string::to_string(mResult.value()["queueArn"].get_string().value);

            // Extract events
            if (mResult.value().find("events") != mResult.value().end()) {
                bsoncxx::document::view eventsView = mResult.value()["events"].get_array().value;
                for (bsoncxx::document::element eventElement: eventsView) {
                    events.emplace_back(eventElement.get_string().value);
                }
            }

            // Extract filter rules
            if (mResult.value().find("filterRules") != mResult.value().end()) {
                bsoncxx::document::view filterRulesView = mResult.value()["filterRules"].get_array().value;
                for (bsoncxx::document::element filterRuleElement: filterRulesView) {
                    FilterRule filterRule;
                    filterRule.FromDocument(filterRuleElement);
                    filterRules.emplace_back(filterRule);
                }
            }

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::DatabaseException(exc.what());
        }
        return *this;
    }

    Poco::JSON::Object QueueNotification::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("id", id);
        jsonObject.set("queueArn", queueArn);

        if (!events.empty()) {
            jsonObject.set("events", Core::JsonUtils::GetJsonStringArray(events));
        }

        if (!filterRules.empty()) {
            Poco::JSON::Array filterRulesArray;
            for (const auto &filterRule: filterRules) {
                filterRulesArray.add(filterRule.ToJsonObject());
            }
            jsonObject.set("filterRules", filterRulesArray);
        }

        return jsonObject;
    }

    void QueueNotification::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("id", jsonObject, id);
        Core::JsonUtils::GetJsonValueString("queueArn", jsonObject, queueArn);

        for (const auto &event: events) {
            events.emplace_back(event);
        }

        Poco::JSON::Array::Ptr jsonFilterRules = jsonObject->getArray("filterRules");
        for (int i = 0; i < jsonFilterRules->size(); i++) {
            FilterRule filterRule;
            filterRule.FromJsonObject(jsonFilterRules->getObject(i));
            filterRules.emplace_back(filterRule);
        }
    }

    std::string QueueNotification::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const QueueNotification &n) {
        os << "QueueNotification=" << bsoncxx::to_json(n.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::S3
