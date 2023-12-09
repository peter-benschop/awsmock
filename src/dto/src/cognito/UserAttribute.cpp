//
// Created by vogje01 on 23/11/2023.
//

#include <awsmock/dto/cognito/UserAttribute.h>

namespace AwsMock::Dto::Cognito {

  void UserAttribute::FromJson(const Poco::JSON::Object::Ptr &object) {

    try {

      Core::JsonUtils::GetJsonValueString("Name", object, name);
      Core::JsonUtils::GetJsonValueString("Value", object, value);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string UserAttribute::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const UserAttribute &r) {
    os << "UserAttribute={name='" << r.name << "', value='" << r.value << "'}";
    return os;
  }
}
