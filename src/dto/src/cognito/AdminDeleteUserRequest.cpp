//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/AdminDeleteUserRequest.h>

namespace AwsMock::Dto::Cognito {

  std::string AdminDeleteUserRequest::ToJson() const {
    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("UserPoolId", userPoolId);
      rootJson.set("Username", userName);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

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
    os << "AdminDeleteUserRequest=" << r.ToJson();
    return os;
  }
}