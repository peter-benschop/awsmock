//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/DeleteUserPoolRequest.h>

namespace AwsMock::Dto::Cognito {

  void DeleteUserPoolRequest::FromJson(const std::string &payload) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(payload);
    const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Core::JsonUtils::GetJsonValueString("UserPoolId", rootObject, id);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string DeleteUserPoolRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteUserPoolRequest &r) {
    os << "DeleteUserPoolRequest={region='" + r.region + "', id='" << r.id << "}";
    return os;
  }
}