//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/CreateSecretRequest.h>

namespace AwsMock::Dto::SecretsManager {

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

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
    }
  }

  std::string CreateSecretRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateSecretRequest &r) {
    os << "CreateQueueRequest={region='" << r.region << "', name='" << r.name << "', clientRequestToken='" << r.clientRequestToken << "', description='" << r.description << "', tags=[";
    for (auto &tag : r.tags) {
      os << tag.first << "='" << tag.second << "', ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "]}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
