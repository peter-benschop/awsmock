//
// Created by vogje01 on 4/25/24.
//

#include <awsmock/dto/kms/Key.h>

namespace AwsMock::Dto::KMS {

    void Key::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            std::string tmpStr;
            Core::JsonUtils::GetJsonValueString("KeyId", rootObject, keyId);
            Core::JsonUtils::GetJsonValueString("KeySpec", rootObject, tmpStr);
            if (!tmpStr.empty()) {
                keySpec = KeySpecFromString(tmpStr);
            }
            Core::JsonUtils::GetJsonValueString("KeyUsage", rootObject, tmpStr);
            if (!tmpStr.empty()) {
                keyUsage = KeyUsageFromString(tmpStr);
            }
            Core::JsonUtils::GetJsonValueString("KeyState", rootObject, tmpStr);
            if (!tmpStr.empty()) {
                keyState = KeyStateFromString(tmpStr);
            }
            Core::JsonUtils::GetJsonValueString("Description", rootObject, description);
            Core::JsonUtils::GetJsonValueBool("MultiRegion", rootObject, multiRegion);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object Key::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("KeyId", keyId);
            rootJson.set("KeySpec", KeySpecToString(keySpec));
            rootJson.set("KeyUsage", KeyUsageToString(keyUsage));
            rootJson.set("KeyState", KeyStateToString(keyState));
            rootJson.set("Description", description);
            rootJson.set("MultiRegion", multiRegion);
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string Key::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string Key::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Key &r) {
        os << "Key=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
