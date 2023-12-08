//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/CreateUserPoolRequest.h>

namespace AwsMock::Dto::Cognito {

  void CreateUserPoolRequest::FromJson(const std::string &payload) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(payload);
    const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("PoolName", rootObject, name);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string CreateUserPoolRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateUserPoolRequest &r) {
    os << "CreateUserPoolRequest={region='" << r.region << "', name=" << r.name << "}";
    return os;
  }
}