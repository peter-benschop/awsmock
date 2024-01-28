//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SendMessageRequest.h>

namespace AwsMock::Dto::SQS {

  void SendMessageRequest::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // General
      Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);
      Core::JsonUtils::GetJsonValueString("MessageBody", rootObject, body);

      // User attributes
      if (rootObject->has("MessageAttributes")) {

        Poco::JSON::Object::Ptr attributesObject = rootObject->getObject("MessageAttributes");

        if (!attributesObject.isNull()) {
          for (size_t i = 0; i < attributesObject->getNames().size(); i++) {
            std::string attributeName = attributesObject->getNames()[i];
            MessageAttribute attributeValue;
            attributeValue.FromJsonObject(attributesObject->getObject(attributeName));
            attributeValue.systemAttribute = false;
            attributes[attributeName] = attributeValue;
          }
        }
      }

      // System attributes
      if (rootObject->has("MessageSystemAttributes")) {

        Poco::JSON::Object::Ptr attributesObject = rootObject->getObject("MessageSystemAttributes");

        if (!attributesObject.isNull()) {
          for (size_t i = 0; i < attributesObject->getNames().size(); i++) {
            std::string attributeName = attributesObject->getNames()[i];
            MessageAttribute attributeValue;
            attributeValue.FromJsonObject(attributesObject->getObject(attributeName));
            attributeValue.systemAttribute = true;
            attributes[attributeName] = attributeValue;
          }
        }
      }
    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string SendMessageRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SendMessageRequest &r) {
    os << "SendMessageRequest={region='" << r.region << "', queueUrl='" << r.queueUrl << "', queueName='" << r.queueName << "', queueArn='" << r.queueArn << "', body: '" << r.body << "', requestId: " << r.requestId << "', userAttributes=[";
    for (const auto &a : r.attributes) {
      os << a.first << "=" << a.second.ToString() << ", ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "]}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
