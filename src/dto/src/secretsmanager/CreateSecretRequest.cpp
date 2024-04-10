//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/CreateSecretRequest.h>

namespace AwsMock::Dto::SecretsManager {

  std::string CreateSecretRequest::ToJson() const {
    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("Name", name);
      rootJson.set("ClientRequestToken", clientRequestToken);
      rootJson.set("Description", description);
      rootJson.set("SecretString", secretString);
      rootJson.set("SecretBinary", secretBinary);
      rootJson.set("ForceOverwriteReplicaSecret", forceOverwriteReplicaSecret);
      rootJson.set("KmsKeyId", kmsKeyId);
      rootJson.set("Tags", tags.ToJsonArray());
      rootJson.set("RequestId", requestId);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::JsonException(exc.message());
    }
  }

  void CreateSecretRequest::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Attributes
      Core::JsonUtils::GetJsonValueString("Name", rootObject, name);
      Core::JsonUtils::GetJsonValueString("ClientRequestToken", rootObject, clientRequestToken);
      Core::JsonUtils::GetJsonValueString("Description", rootObject, description);
      Core::JsonUtils::GetJsonValueString("SecretString", rootObject, secretString);
      Core::JsonUtils::GetJsonValueString("SecretBinary", rootObject, secretBinary);
      Core::JsonUtils::GetJsonValueBool("ForceOverwriteReplicaSecret", rootObject, forceOverwriteReplicaSecret);
      Core::JsonUtils::GetJsonValueString("KmsKeyId", rootObject, kmsKeyId);
      tags.FromJson(rootObject->getObject("Tags"));

    } catch (Poco::Exception &exc) {
      throw Core::JsonException(exc.message());
    }
  }

  std::string CreateSecretRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateSecretRequest &r) {
    os << "CreateQueueRequest=" << r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::SQS
