//
// Created by vogje01 on 4/20/24.
//

#include <awsmock/dto/cognito/PreTokenGenerationConfig.h>

namespace AwsMock::Dto::Cognito {

  std::string PreTokenGenerationConfig::ToJson() const {

    try {

      Poco::JSON::Object rootJson;
      rootJson.set("lambdaArn", lambdaArn);
      rootJson.set("lambdaVersion", lambdaVersion);

      return Core::JsonUtils::ToJsonString(rootJson);

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  Poco::JSON::Object PreTokenGenerationConfig::ToJsonObject() const {

    try {

      Poco::JSON::Object rootJson;
      rootJson.set("lambdaArn", lambdaArn);
      rootJson.set("lambdaVersion", lambdaVersion);

      return rootJson;

    } catch (Poco::Exception &exc) {
      log_error << exc.message();
      throw Core::JsonException(exc.message());
    }
  }

  std::string PreTokenGenerationConfig::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const PreTokenGenerationConfig &r) {
    os << "PreTokenGenerationConfig=" << r.ToJson();
    return os;
  }

}