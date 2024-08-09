//
// Created by vogje01 on 23/11/2023.
//

#include "awsmock/dto/cognito/model/UserAttribute.h"

namespace AwsMock::Dto::Cognito {

    std::string UserAttribute::ToJson() const {

        try {
            Poco::JSON::Object rootObject;
            rootObject.set("Name", name);
            rootObject.set("Value", value);

            std::ostringstream os;
            rootObject.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void UserAttribute::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("Name", jsonObject, name);
            Core::JsonUtils::GetJsonValueString("Value", jsonObject, value);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string UserAttribute::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UserAttribute &r) {
        os << "UserAttribute=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito
