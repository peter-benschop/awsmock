//
// Created by vogje01 on 06/09/2023.
//

#include <awsmock/dto/lambda/Function.h>

namespace AwsMock::Dto::Lambda {

  Poco::JSON::Object Function::ToJsonObject() const {

    try {
      Poco::JSON::Object rootJson;

      // Architectures array
      Poco::JSON::Array architectureArray;
      for (const auto &architecture : architectures) {
        architectureArray.add(architecture);
      }
      rootJson.set("Architectures", architectureArray);

      rootJson.set("CodeSha256", codeSha256);
      rootJson.set("CodeSize", codeSize);
      rootJson.set("DeadLetterConfig", deadLetterConfig.ToJsonObject());
      rootJson.set("Description", description);
      // TODO: Environment, EphemeralStorage, FileSystemConfig
      rootJson.set("FunctionArn", functionArn);
      rootJson.set("FunctionName", functionName);
      rootJson.set("Handler", handler);
      rootJson.set("FunctionName", functionName);
      // TODO: ImageConfig
      rootJson.set("LastModified", Poco::DateTimeFormatter().format(lastModified, Poco::DateTimeFormat::HTTP_FORMAT));
      rootJson.set("LastUpdateStatus", lastUpdateStatusReason);
      rootJson.set("LastUpdateStatusCode", lastUpdateStatusReasonCode);
      rootJson.set("State", state);
      rootJson.set("StateResaon", stateReason);
      rootJson.set("StateReasonCode", stateReasonCode);
      rootJson.set("Timeout", timeout);
      rootJson.set("Environment", environment.ToJson());
      rootJson.set("Version", version);

      return rootJson;

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string Function::ToJson() const {
    return Core::JsonUtils::ToJsonString(ToJsonObject());
  }

  std::string Function::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Function &f) {
    os << "Function=" << f.ToJson();
    return os;
  }
}
