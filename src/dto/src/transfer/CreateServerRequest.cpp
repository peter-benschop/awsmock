//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/transfer/CreateServerRequest.h>

namespace AwsMock::Dto::Transfer {

  std::string CreateServerRequest::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("region", region);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  void CreateServerRequest::FromJson(const std::string &body) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(body);
    Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {
      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Poco::JSON::Array::Ptr protocolsArray = rootObject->getArray("Protocols");
      if (protocolsArray != nullptr) {
        for (const auto &protocol : *protocolsArray) {
          protocols.push_back(protocol.convert<std::string>());
        }
      }

      // Cleanup
      rootObject->clear();
      parser.reset();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string CreateServerRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateServerRequest &r) {
    os << "CreateServerRequest={region='" << r.region << "' {";
    for (const auto &tag : r.tags) {
      os << tag.ToString();
    }
    os << "}";
    return os;
  }

} // namespace AwsMock::Dto::lambda
