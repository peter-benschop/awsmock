//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/Port.h>

namespace AwsMock::Dto::Docker {

  Port::Port(const Poco::JSON::Object::Ptr &object) {
    FromJson(object);
  }

  void Port::FromJson(const Poco::JSON::Object::Ptr &object) {

    try {

      Core::JsonUtils::GetJsonValueInt("PrivatePort", object, privatePort);
      Core::JsonUtils::GetJsonValueInt("PublicPort", object, publicPort);
      Core::JsonUtils::GetJsonValueString("Type", object, type);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string Port::ToJson() const {

    try {

      Poco::JSON::Object rootJson;
      rootJson.set("privatePort", privatePort);
      rootJson.set("publicPort", publicPort);
      rootJson.set("type", type);

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string Port::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Port &p) {
    os << "Port=" << p.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::Docker
