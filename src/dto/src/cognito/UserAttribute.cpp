//
// Created by vogje01 on 23/11/2023.
//

#include <awsmock/dto/cognito/UserAttribute.h>

namespace AwsMock::Dto::Cognito {

  std::string UserAttribute::ToJson() const {

    try {
      Poco::JSON::Object rootObject;
      rootObject.set("Name", name);
      rootObject.set("Value", value);

      std::ostringstream os;
      rootObject.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  void UserAttribute::FromJson(const Poco::JSON::Object::Ptr &object) {

    try {

      Core::JsonUtils::GetJsonValueString("Name", object, name);
      Core::JsonUtils::GetJsonValueString("Value", object, value);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string UserAttribute::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const UserAttribute &r) {
    os << "UserAttribute=" << r.ToJson();
    return os;
  }
}
