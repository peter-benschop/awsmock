//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/Port.h>

namespace AwsMock::Dto::Docker {

  Port::Port(const Poco::JSON::Object::Ptr &object) {
    FromJson(object);
  }

  void Port::FromJson(Poco::JSON::Object::Ptr object) {

    try {

      Core::JsonUtils::GetJsonValueInt("PrivatePort", object, privatePort);
      Core::JsonUtils::GetJsonValueInt("PublicPort", object, publicPort);
      Core::JsonUtils::GetJsonValueString("Type", object, type);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string Port::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Port &p) {
    os << "Port={privatePort=" << p.privatePort << ", publicPort=" << p.publicPort << ", type='" << p.type << "'}";
    return os;
  }

} // namespace AwsMock::Dto::Docker
