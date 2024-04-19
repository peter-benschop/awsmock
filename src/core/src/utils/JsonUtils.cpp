
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Core {

  void JsonUtils::GetJsonValueString(const std::string &name, Poco::JSON::Object::Ptr jsonObject, std::string &attribute) {
    if (jsonObject->has(name)) {
      attribute = jsonObject->get(name).convert<std::string>();
    }
  }

  void JsonUtils::GetJsonValueLong(const std::string &name, Poco::JSON::Object::Ptr jsonObject, long &attribute) {
    if (jsonObject->has(name)) {
      attribute = jsonObject->get(name).convert<long>();
    }
  }

  void JsonUtils::GetJsonValueDouble(const std::string &name, Poco::JSON::Object::Ptr jsonObject, double &attribute) {
    if (jsonObject->has(name)) {
      attribute = jsonObject->get(name).convert<double>();
    }
  }

  void JsonUtils::GetJsonValueFloat(const std::string &name, Poco::JSON::Object::Ptr jsonObject, float &attribute) {
    if (jsonObject->has(name)) {
      attribute = jsonObject->get(name).convert<float>();
    }
  }

  void JsonUtils::GetJsonValueInt(const std::string &name, Poco::JSON::Object::Ptr jsonObject, int &attribute) {
    if (jsonObject->has(name)) {
      attribute = jsonObject->get(name).convert<int>();
    }
  }

  void JsonUtils::GetJsonValueBool(const std::string &name, Poco::JSON::Object::Ptr jsonObject, bool &attribute) {
    if (jsonObject->has(name)) {
      attribute = jsonObject->get(name).convert<bool>();
    }
  }

  void JsonUtils::GetJsonValueDate(const std::string &name, Poco::JSON::Object::Ptr jsonObject, Poco::DateTime &attribute) {
    if (jsonObject->has(name)) {
      int tz;
      auto stringValue = jsonObject->get(name).convert<std::string>();
      Poco::DateTimeParser::parse(Poco::DateTimeFormat::ISO8601_FRAC_FORMAT, stringValue, attribute, tz);
    }
  }

  Poco::JSON::Array JsonUtils::GetJsonStringArray(const std::vector<std::string> &values) {

    Poco::JSON::Array jsonArray;
    for (const auto &it : values) {
      jsonArray.add(it);
    }
    return jsonArray;
  }

  Poco::JSON::Object JsonUtils::GetJsonObject(const std::map<std::string, std::string> &values) {

    Poco::JSON::Object jsonObject;
    for (const auto &it : values) {
      jsonObject.set(it.first, it.second);
    }
    return jsonObject;
  }

  std::string JsonUtils::ToJsonString(const Poco::JSON::Object &jsonObject) {

    std::ostringstream os;
    jsonObject.stringify(os);
    return os.str();
  }

}