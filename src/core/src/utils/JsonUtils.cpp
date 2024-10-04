
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Core {

    void JsonUtils::GetJsonValueString(const std::string &name, Poco::JSON::Object::Ptr jsonObject, std::string &attribute) {
        if (jsonObject->has(name)) {
            attribute = jsonObject->get(name).convert<std::string>();
        }
    }

    void JsonUtils::SetJsonValueString(Poco::JSON::Object &jsonObject, const std::string &name, const std::string &value) {
        if (!value.empty()) {
            jsonObject.set(name, value);
        }
    }

    void JsonUtils::GetJsonValueLong(const std::string &name, Poco::JSON::Object::Ptr jsonObject, long &attribute) {
        if (jsonObject->has(name)) {
            attribute = jsonObject->get(name).convert<long>();
        }
    }

    void JsonUtils::SetJsonValueLong(Poco::JSON::Object &jsonObject, const std::string &name, long value) {
        jsonObject.set(name, value);
    }

    void JsonUtils::GetJsonValueDouble(const std::string &name, Poco::JSON::Object::Ptr jsonObject, double &attribute) {
        if (jsonObject->has(name)) {
            attribute = jsonObject->get(name).convert<double>();
        }
    }

    void JsonUtils::SetJsonValueDouble(Poco::JSON::Object &jsonObject, const std::string &name, double value) {
        jsonObject.set(name, value);
    }

    void JsonUtils::GetJsonValueFloat(const std::string &name, Poco::JSON::Object::Ptr jsonObject, float &attribute) {
        if (jsonObject->has(name)) {
            attribute = jsonObject->get(name).convert<float>();
        }
    }

    void JsonUtils::SetJsonValueFloat(Poco::JSON::Object &jsonObject, const std::string &name, float value) {
        jsonObject.set(name, value);
    }

    void JsonUtils::GetJsonValueInt(const std::string &name, Poco::JSON::Object::Ptr jsonObject, int &attribute) {
        if (jsonObject->has(name)) {
            attribute = jsonObject->get(name).convert<int>();
        }
    }

    void JsonUtils::SetJsonValueInt(Poco::JSON::Object &jsonObject, const std::string &name, int value) {
        jsonObject.set(name, value);
    }

    void JsonUtils::GetJsonValueBool(const std::string &name, Poco::JSON::Object::Ptr jsonObject, bool &attribute) {
        if (jsonObject->has(name)) {
            attribute = jsonObject->get(name).convert<bool>();
        }
    }

    void JsonUtils::SetJsonValueBool(Poco::JSON::Object &jsonObject, const std::string &name, bool value) {
        jsonObject.set(name, value);
    }

    void JsonUtils::GetJsonValueDate(const std::string &name, Poco::JSON::Object::Ptr jsonObject, Poco::DateTime &attribute) {
        if (jsonObject->has(name)) {
            int tz;
            auto stringValue = jsonObject->get(name).convert<std::string>();
            Poco::DateTimeParser::parse(Poco::DateTimeFormat::ISO8601_FRAC_FORMAT, stringValue, attribute, tz);
        }
    }

    void JsonUtils::GetJsonValueDate(const std::string &name, Poco::JSON::Object::Ptr jsonObject, std::chrono::system_clock::time_point &attribute) {
        if (jsonObject->has(name)) {
            auto stringValue = jsonObject->get(name).convert<std::string>();
            std::tm t = {};
            strptime(stringValue.c_str(), "%FT%T%z", &t);
            attribute = std::chrono::system_clock::from_time_t(mktime(&t));
        }
    }

    Poco::JSON::Array JsonUtils::GetJsonStringArray(const std::vector<std::string> &values) {

        Poco::JSON::Array jsonArray;
        for (const auto &it: values) {
            jsonArray.add(it);
        }
        return jsonArray;
    }

    Poco::JSON::Object JsonUtils::GetJsonObject(const std::map<std::string, std::string> &values) {

        Poco::JSON::Object jsonObject;
        for (const auto &it: values) {
            jsonObject.set(it.first, it.second);
        }
        return jsonObject;
    }

    std::string JsonUtils::ToJsonString(const Poco::JSON::Object &jsonObject, bool prettyPrint, int indent) {

        std::ostringstream os;
        if (prettyPrint) {
            jsonObject.stringify(os, indent);
        } else {
            jsonObject.stringify(os);
        }
        return os.str();
    }

    std::string JsonUtils::ToJsonString(const Poco::JSON::Array &jsonArray, bool prettyPrint, int indent) {

        std::ostringstream os;
        if (prettyPrint) {
            jsonArray.stringify(os, indent);
        } else {
            jsonArray.stringify(os);
        }
        return os.str();
    }

}// namespace AwsMock::Core