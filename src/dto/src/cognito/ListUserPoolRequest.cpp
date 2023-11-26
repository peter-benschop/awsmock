//
// Created by vogje01 on 11/25/23.
//

#include <awsmock/dto/cognito/ListUserPoolRequest.h>

namespace AwsMock::Dto::Cognito {

  void ListUserPoolRequest::FromJson(const std::string &payload) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(payload);
    const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {
      Core::JsonUtils::GetJsonValueInt("MaxResults", rootObject, maxResults);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string ListUserPoolRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ListUserPoolRequest &r) {
    os << "ListUserPoolRequest={region='" << r.region << "', maxResults=" << r.maxResults << "}";
    return os;
  }
}