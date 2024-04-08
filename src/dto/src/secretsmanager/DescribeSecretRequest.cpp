//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/DescribeSecretRequest.h>

namespace AwsMock::Dto::SecretsManager {

  void DescribeSecretRequest::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Attributes
      Core::JsonUtils::GetJsonValueString("Name", rootObject, name);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
    }
  }

  std::string DescribeSecretRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DescribeSecretRequest &r) {
    os << "DescribeSecretRequest={region='" << r.region << "', name='" << r.name << "'}";
    return os;
  }

} // namespace AwsMock::Dto::S3
