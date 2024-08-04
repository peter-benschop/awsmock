//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/cognito/model/TokenValidityUnits.h>

namespace AwsMock::Dto::Cognito {

    std::string TokenValidityUnits::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object TokenValidityUnits::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("AccessToken", ValidityUnitToString(accessToken));
            rootJson.set("IdToken", ValidityUnitToString(idToken));
            rootJson.set("RefreshToken", ValidityUnitToString(refreshToken));

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void TokenValidityUnits::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {
        std::string tmp;
        Core::JsonUtils::GetJsonValueString("AccessToken", jsonObject, tmp);
        accessToken = ValidityUnitFromString(tmp);
        Core::JsonUtils::GetJsonValueString("IdToken", jsonObject, tmp);
        idToken = ValidityUnitFromString(tmp);
        Core::JsonUtils::GetJsonValueString("RefreshToken", jsonObject, tmp);
        refreshToken = ValidityUnitFromString(tmp);
    }

    std::string TokenValidityUnits::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TokenValidityUnits &o) {
        os << "TokenValidityUnits=" << o.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::Cognito
