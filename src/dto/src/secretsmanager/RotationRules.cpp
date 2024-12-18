//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/RotationRules.h>

namespace AwsMock::Dto::SecretsManager {

    view_or_value<view, value> RotationRules::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetIntValue(document, "AutomaticallyAfterDays", automaticallyAfterDays);
            Core::Bson::BsonUtils::SetStringValue(document, "Duration", duration);
            Core::Bson::BsonUtils::SetStringValue(document, "ScheduleExpression", scheduleExpression);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void RotationRules::FromDocument(const view_or_value<view, value> &document) {

        try {

            automaticallyAfterDays = Core::Bson::BsonUtils::GetIntValue(document, "Duration");
            duration = Core::Bson::BsonUtils::GetStringValue(document, "Duration");
            scheduleExpression = Core::Bson::BsonUtils::GetStringValue(document, "scheduleExpression");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string RotationRules::ToJson() const {
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
    }

    std::string RotationRules::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const RotationRules &r) {
        os << "RotationRules=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SecretsManager