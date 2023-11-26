//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/sqs/SetQueueAttributesRequest.h>

namespace AwsMock::Dto::SQS {

  void SetQueueAttributesRequest::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Attributes
      Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);
      Poco::JSON::Array::Ptr attributesArray = rootObject->getArray("Attributes");

      if (rootObject->has("Attributes")) {
        Poco::JSON::Object::Ptr attributesObject = rootObject->getObject("Attributes");
        for (const auto &key : attributesObject->getNames()) {
          std::string value;
          Core::JsonUtils::GetJsonValueString(key, attributesObject, value);
          attributes[key] = value;
        }
      }

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string SetQueueAttributesRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SetQueueAttributesRequest &r) {
    os << "SetQueueAttributesRequest={queueUrl='" << r.queueUrl + "', resource='" << r.resource + "', requestId='" << r.requestId << "', attributes={";
    for (auto &attribute : r.attributes) {
      os << attribute.first << "='" << attribute.second << "', ";
    }
    os << "\b\b" << "}}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
