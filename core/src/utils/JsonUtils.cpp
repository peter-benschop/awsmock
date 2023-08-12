
#include "awsmock/core/JsonUtils.h"

namespace AwsMock::Core {

    void JsonUtils::GetJsonValueString(const std::string &name, Poco::JSON::Object::Ptr jsonObject, std::string &attribute) {
        if(jsonObject->has(name)) {
            attribute = jsonObject->get(name).convert<std::string>();
        }
    }

    void JsonUtils::GetJsonValueLong(const std::string &name, Poco::JSON::Object::Ptr jsonObject, long &attribute) {
        if(jsonObject->has(name)) {
            attribute = jsonObject->get(name).convert<long>();
        }
    }
}