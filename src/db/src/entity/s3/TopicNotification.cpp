//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/entity/s3/TopicNotification.h>

namespace AwsMock::Database::Entity::S3 {

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
                if (mResult.value().find("filterRules") != mResult.value().end()) {
                    bsoncxx::document::view filterRulesView = mResult.value()["filterRules"].get_document().value;
                    for (bsoncxx::document::element filterRuleElement: filterRulesView) {
                        FilterRule filterRule;
                        filterRule.FromDocument(filterRuleElement);
                        filterRules.emplace_back(filterRule);
                    }
                }
            }

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::DatabaseException(exc.what());
        }
        return *this;
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
