//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/AdminDeleteUserRequest.h>

namespace AwsMock::Dto::Cognito {

  void AdminDeleteUserRequest::FromJson(const std::string &payload) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(payload);
    const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);
      Core::JsonUtils::GetJsonValueString("Username", rootObject, userName);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string AdminDeleteUserRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const AdminDeleteUserRequest &r) {
    os << "AdminDeleteUserRequest={region='" << r.region << "', userPoolId='" << r.userPoolId << "', userName='" << r.userName << "'}";
    return os;
  }
}