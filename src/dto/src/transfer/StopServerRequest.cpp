//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/StopServerRequest.h>

namespace AwsMock::Dto::Transfer {

  void StopServerRequest::FromJson(const std::string &body) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(body);
    const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Get root values
      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("ServerId", rootObject, serverId);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string StopServerRequest::ToJson() const {

    try {

      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("ServerId", serverId);

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string StopServerRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const StopServerRequest &r) {
    os << "StopServerRequest=" << r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::lambda
