//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/entity/s3/TopicNotification.h>

namespace AwsMock::Database::Entity::S3 {

    bool TopicNotification::CheckFilter(const std::string &key) {

        if (filterRules.empty()) {
            return true;
        }

        return std::ranges::any_of(filterRules, [key](const FilterRule &rule) {
            return (rule.name == "prefix" && key.starts_with(rule.value)) || (rule.name == "suffix" && key.ends_with(rule.value));
        });
    }

    view_or_value<view, value> TopicNotification::ToDocument() const {

        auto topicNotificationDoc = bsoncxx::builder::basic::document{};
        topicNotificationDoc.append(kvp("id", id));
        topicNotificationDoc.append(kvp("topicArn", topicArn));

        // Events
        auto eventsDoc = bsoncxx::builder::basic::array{};
        for (const auto &event: events) {
            eventsDoc.append(event);
        }
        topicNotificationDoc.append(kvp("events", eventsDoc));

        auto filterRulesDoc = bsoncxx::builder::basic::array{};
        for (const auto &filterRule: filterRules) {
            filterRulesDoc.append(filterRule.ToDocument());
        }
        topicNotificationDoc.append(kvp("filterRules", filterRulesDoc));

        return topicNotificationDoc.extract();
    }

    TopicNotification TopicNotification::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        try {

            id = bsoncxx::string::to_string(mResult.value()["id"].get_string().value);
            topicArn = bsoncxx::string::to_string(mResult.value()["topicArn"].get_string().value);

            // Extract filter rules
            if (mResult.value().find("filterRules") != mResult.value().end()) {
                bsoncxx::array::view filterRulesView{mResult.value()["filterRules"].get_array().value};
                for (const bsoncxx::array::element &filterRuleElement: filterRulesView) {
                    FilterRule filterRule;
                    filterRule.FromDocument(filterRuleElement.get_document());
                    filterRules.emplace_back(filterRule);
                }
            }

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::DatabaseException(exc.what());
        }
        return *this;
    }

    void TopicNotification::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("id", jsonObject, id);
        Core::JsonUtils::GetJsonValueString("topicArn", jsonObject, topicArn);

        // Events
        for (const auto &event: events) {
            events.emplace_back(event);
        }

        // Filter rules
        if (jsonObject->has("filterRules")) {
            Poco::JSON::Array::Ptr jsonFilterRules = jsonObject->getArray("filterRules");
            for (int i = 0; i < jsonFilterRules->size(); i++) {
                FilterRule filterRule;
                filterRule.FromJsonObject(jsonFilterRules->getObject(i));
                filterRules.emplace_back(filterRule);
            }
        }
    }

    Poco::JSON::Object TopicNotification::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("id", id);
        jsonObject.set("topicArn", topicArn);

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

    std::string TopicNotification::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TopicNotification &n) {
        os << "TopicNotification=" << bsoncxx::to_json(n.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::S3
