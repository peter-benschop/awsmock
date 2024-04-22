//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/dto/docker/CreateContainerResponse.h>

namespace AwsMock::Dto::Docker {

  void CreateContainerResponse::FromJson(const std::string &jsonString) {

    if (jsonString.empty()) {
      return;
    }

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {
      Core::JsonUtils::GetJsonValueString("Id", rootObject, id);
    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string CreateContainerResponse::ToJson() const {

    try {

      Poco::JSON::Object rootJson;
      rootJson.set("id", id);
      rootJson.set("hostPort", hostPort);

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string CreateContainerResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateContainerResponse &r) {
    os << "CreateContainerResponse=" << r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::Docker
