//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/RotationRules.h>

namespace AwsMock::Dto::SecretsManager {

    Poco::JSON::Object RotationRules::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("AutomaticallyAfterDays", automaticallyAfterDays);
            rootJson.set("Duration", duration);
            rootJson.set("ScheduleExpression", scheduleExpression);
            return rootJson;

        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message());
        }
    }

    std::string RotationRules::ToJson() const {

        std::ostringstream os;
        ToJsonObject().stringify(os);
        return os.str();
    }

    void RotationRules::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueLong("AutomaticallyAfterDays", jsonObject, automaticallyAfterDays);
            Core::JsonUtils::GetJsonValueString("Duration", jsonObject, duration);
            Core::JsonUtils::GetJsonValueString("ScheduleExpression", jsonObject, scheduleExpression);

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            throw Core::ServiceException(exc.message());
        }
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