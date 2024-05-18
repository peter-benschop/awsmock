//
// Created by vogje01 on 4/25/24.
//

#include "awsmock/dto/kms/model/ListKey.h"

namespace AwsMock::Dto::KMS {

    void ListKey::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            std::string tmpStr;
            Core::JsonUtils::GetJsonValueString("KeyId", rootObject, keyId);
            Core::JsonUtils::GetJsonValueString("KeyArn", rootObject, keyArn);
            std::string keyStateStr;
            Core::JsonUtils::GetJsonValueString("KeyState", rootObject, keyStateStr);
            if (!keyStateStr.empty()) {
                keyState = KeyStateFromString(keyStateStr);
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object ListKey::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("KeyId", keyId);
            rootJson.set("KeyArn", keyArn);
            rootJson.set("KeyState", KeyStateToString(keyState));
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string ListKey::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string ListKey::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListKey &r) {
        os << "ListKey=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::KMS
