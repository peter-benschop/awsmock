//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/AdminCreateUserResponse.h>

namespace AwsMock::Dto::Cognito {

  void AdminCreateUserResponse::FromJson(const std::string &payload) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(payload);
    const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("UserName", rootObject, userName);

      Poco::JSON::Array::Ptr attributesArray = rootObject->getArray("UserAttributes");

      if (attributesArray != nullptr) {
        for (const auto &it : *attributesArray) {
          if(!it.isEmpty()) {
            const auto& object =  it.extract<Poco::JSON::Object::Ptr>();
            UserAttribute userAttribute;
            userAttribute.FromJson(object);
            userAttributes.emplace_back(userAttribute);
          }
        }
      }

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string AdminCreateUserResponse::ToJson() {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("User", enabled);
      rootJson.set("Enabled", enabled);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string AdminCreateUserResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const AdminCreateUserResponse &r) {
    os << "AdminCreateUserResponse={region='" << r.region << "', userName='" << r.userName << "', userName='" << r.userName << "', userAttributes=[";
    for (const auto& attribute : r.userAttributes) {
      os << attribute.name << "='" << attribute.value << "', ";
    }
    os << "\b\b\b" << "]}";
    return os;
  }
}