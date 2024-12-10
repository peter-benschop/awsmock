//
// Created by vogje01 on 24/09/2023.
//

#include <awsmock/entity/secretsmanager/RotationRules.h>

namespace AwsMock::Database::Entity::SecretsManager {

    view_or_value<view, value> RotationRules::ToDocument() const {

        auto rotationRulesDoc = document{};
        rotationRulesDoc.append(kvp("automaticallyAfterDays", static_cast<bsoncxx::types::b_int64>(automaticallyAfterDays)));
        rotationRulesDoc.append(kvp("duration", duration));
        rotationRulesDoc.append(kvp("scheduleExpression", scheduleExpression));

        return rotationRulesDoc.extract();
    }

    void RotationRules::FromDocument(std::optional<view> mResult) {

        automaticallyAfterDays = mResult.value()["automaticallyAfterDays"].get_int64().value;
        duration = bsoncxx::string::to_string(mResult.value()["duration"].get_string().value);
        scheduleExpression = bsoncxx::string::to_string(mResult.value()["scheduleExpression"].get_string().value);
    }

    std::string RotationRules::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const RotationRules &s) {
        os << "RotationRules=" << to_json(s.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SecretsManager
