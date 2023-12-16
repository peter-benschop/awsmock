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

      // Attributes
      Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);
      Core::JsonUtils::GetJsonValueString("MessageBody", rootObject, body);
      Poco::JSON::Array::Ptr attributesArray = rootObject->getArray("MessageAttributes");

      if (attributesArray != nullptr) {
        for (const auto &it : *attributesArray) {
          //attributeNames.emplace_back(it.extract<std::string>());
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
    for (const auto &a : r.messageAttributes) {
      os << a.ToString() << ", ";
    }
    os << "\b" << "\b" << "]}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
