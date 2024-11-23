//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/dto/cognito/model/User.h>

namespace AwsMock::Dto::Cognito {

    std::string User::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    Poco::JSON::Object User::ToJsonObject() const {
        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("userName", userName);
        jsonObject.set("userPoolId", userPoolId);
        jsonObject.set("enabled", enabled);
        //jsonObject.set("userStatus", Entity::Cognito::UserStatusToString(userStatus));

        // Attributes
        /*if (!userAttributes.empty()) {
            Poco::JSON::Array jsonAttributeArray;
            for (const auto &attribute: userAttributes) {
                Poco::JSON::Object jsonAttribute;
                jsonAttribute.set("name", attribute.name);
                jsonAttribute.set("value", attribute.value);
                jsonAttributeArray.add(jsonAttribute);
            }
            jsonObject.set("userAttributes", jsonAttributeArray);
        }*/

        return jsonObject;
    }

    void User::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
        Core::JsonUtils::GetJsonValueString("userName", jsonObject, userName);
        Core::JsonUtils::GetJsonValueString("userPoolId", jsonObject, userPoolId);
        Core::JsonUtils::GetJsonValueBool("enabled", jsonObject, enabled);
        std::string userStatusStr;
        Core::JsonUtils::GetJsonValueString("userStatus", jsonObject, userStatusStr);
        //userStatus = UserStatusFromString(userStatusStr);

        /*if (jsonObject->has("userAttributes")) {
            Poco::JSON::Array::Ptr jsonAttributeArray = jsonObject->getArray("userAttributes");
            for (int i = 0; i < jsonAttributeArray->size(); i++) {
                UserAttribute userAttribute;
                Poco::JSON::Object::Ptr jsonAttributeObject = jsonAttributeArray->getObject(i);
                Core::JsonUtils::GetJsonValueString("name", jsonAttributeObject, userAttribute.name);
                Core::JsonUtils::GetJsonValueString("value", jsonAttributeObject, userAttribute.value);
                userAttributes.emplace_back(userAttribute);
            }
        }*/
    }

    std::string User::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const User &u) {
        os << "User=" << u.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::Cognito