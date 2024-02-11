//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/CreateQueueRequest.h>

namespace AwsMock::Dto::SQS {

  void CreateQueueRequest::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Attributes
      Core::JsonUtils::GetJsonValueString("QueueName", rootObject, queueName);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string CreateQueueRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateQueueRequest &r) {
    os << "CreateQueueRequest={region='" << r.region << "', queueUrl='" << r.queueUrl << "', queueName='" << r.queueName << "', owner='" << r.owner << "', userAttributes=[";
    for (auto &attribute : r.attributes) {
      os << attribute.attributeName << "='" << attribute.attributeValue << "', ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "], tags=[";
    for (auto &tag : r.tags) {
      os << tag.first << "='" << tag.second << "', ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "]}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
