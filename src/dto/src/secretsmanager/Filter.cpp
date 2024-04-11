//
// Created by vogje01 on 4/8/24.
//

#include <awsmock/dto/secretsmanager/Filter.h>

namespace AwsMock::Dto::SecretsManager {

  Poco::JSON::Object Filter::ToJsonObject() const {

    try {

      Poco::JSON::Object rootJson;
      rootJson.set("Key", key);

      Poco::JSON::Array valueArray;
      for(const auto &v : values) {
        valueArray.add(v);
      }
      rootJson.set("Values", valueArray);
      return rootJson;

    } catch (Poco::Exception &exc) {
      throw Core::JsonException(exc.message());
    }
  }

  std::string Filter::ToJson() const {

    std::ostringstream os;
    ToJsonObject().stringify(os);
    return os.str();
  }

  void Filter::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

    try {

      Core::JsonUtils::GetJsonValueString("Key", jsonObject, key);
      Poco::JSON::Array::Ptr jsonValueArray = jsonObject->getArray("Values");
      for (std::size_t i = 0; i < jsonValueArray->size(); i++) {
        std::string value = jsonValueArray->getElement<std::string>(i);
        values.emplace_back(value);
      }
    } catch (Poco::Exception &exc) {
      throw Core::JsonException(exc.message());
    }
  }

  std::string Filter::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Filter &tags) {
    os << "Filter=" << tags.ToJson();
    return os;
  }
}