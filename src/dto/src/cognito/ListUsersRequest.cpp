//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUsersRequest.h>

namespace AwsMock::Dto::Cognito {

  void ListUsersRequest::FromJson(const std::string &payload) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(payload);
    const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, userPoolId);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string ListUsersRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ListUsersRequest &r) {
    os << "ListUsersRequest={region='" << r.region << "', userPoolId=" << r.userPoolId << "}";
    return os;
  }
}