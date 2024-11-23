//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/ValidationData.h>

namespace AwsMock::Dto::Cognito {

    std::string ValidationData::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void ValidationData::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("Name", jsonObject, name);
            Core::JsonUtils::GetJsonValueString("Value", jsonObject, value);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object ValidationData::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Name", name);
            rootJson.set("Value", value);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ValidationData::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ValidationData &o) {
        os << "ValidationData=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
