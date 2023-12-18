//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/StopServerRequest.h>

namespace AwsMock::Dto::Transfer {

  void StopServerRequest::FromJson(const std::string &body) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(body);
    const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Get root values
      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("ServerId", rootObject, serverId);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string StopServerRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const StopServerRequest &r) {
    os << "StopServerRequest={region='" << r.region << "' serverId='" << r.serverId << "'}";
    return os;
  }

} // namespace AwsMock::Dto::lambda
