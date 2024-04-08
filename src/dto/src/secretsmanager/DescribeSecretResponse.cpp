//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/secretsmanager/DescribeSecretResponse.h>

namespace AwsMock::Dto::SecretsManager {

  std::string DescribeSecretResponse::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Name", name);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void DescribeSecretResponse::FromJson(const std::string &jsonString) {

    try {
      Poco::JSON::Parser parser;
      Poco::Dynamic::Var result = parser.parse(jsonString);

      const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();
      Core::JsonUtils::GetJsonValueString("Name", rootObject, name);

    } catch (Poco::Exception &exc) {
      std::cerr << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string DescribeSecretResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DescribeSecretResponse &r) {
    os << "DescribeSecretResponse={name='" << r.name << "', region='" << r.region << "'}";
    return os;
  }

} // namespace AwsMock::Dto
