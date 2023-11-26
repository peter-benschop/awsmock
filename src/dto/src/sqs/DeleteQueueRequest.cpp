//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteQueueRequest.h>

namespace AwsMock::Dto::SQS {

  void DeleteQueueRequest::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Attributes
      Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string DeleteQueueRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteQueueRequest &r) {
    os << "DeleteQueueRequest={queueUrl='" + r.queueUrl + "' resource='" + r.resource + "' requestId='" + r.requestId + "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
