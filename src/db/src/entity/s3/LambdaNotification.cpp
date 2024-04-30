//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/entity/s3/LambdaNotification.h>

namespace AwsMock::Database::Entity::S3 {

    bool LambdaNotification::CheckFilter(const std::string &key) {

        if (filterRules.empty()) {
            return true;
        }

        return std::ranges::any_of(filterRules, [key](const FilterRule &rule) {
            return (rule.name == "prefix" && key.starts_with(rule.value)) || (rule.name == "suffix" && key.ends_with(rule.value));
        });
    }

    view_or_value<view, value> LambdaNotification::ToDocument() const {

        auto lambdaNotificationDoc = bsoncxx::builder::basic::document{};
        lambdaNotificationDoc.append(kvp("id", id));
        lambdaNotificationDoc.append(kvp("lambdaArn", lambdaArn));

        // Events
        auto eventsDoc = bsoncxx::builder::basic::array{};
        for (const auto &event: events) {
            eventsDoc.append(event);
        }
        lambdaNotificationDoc.append(kvp("events", eventsDoc));

        auto filterRulesDoc = bsoncxx::builder::basic::array{};
        for (const auto &filterRule: filterRules) {
            filterRulesDoc.append(filterRule.ToDocument());
        }
        lambdaNotificationDoc.append(kvp("filterRules", filterRulesDoc));

        return lambdaNotificationDoc.extract();
    }

    LambdaNotification LambdaNotification::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        try {

            id = bsoncxx::string::to_string(mResult.value()["id"].get_string().value);
            lambdaArn = bsoncxx::string::to_string(mResult.value()["lambdaArn"].get_string().value);

            // Extract events
            if (mResult.value().find("events") != mResult.value().end()) {
                bsoncxx::document::view eventsView = mResult.value()["events"].get_array().value;
                for (bsoncxx::document::element event: eventsView) {
                    events.emplace_back(event.get_string().value);
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

    Poco::JSON::Object LambdaNotification::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("id", id);
        jsonObject.set("lambdaArn", lambdaArn);

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

    std::string LambdaNotification::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const LambdaNotification &n) {
        os << "LambdaNotification=" << bsoncxx::to_json(n.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::S3
