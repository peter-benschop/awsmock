//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteMessageRequest.h>

namespace AwsMock::Dto::SQS {

  void DeleteMessageRequest::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Attributes
      Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);
      Core::JsonUtils::GetJsonValueString("ReceiptHandle", rootObject, receiptHandle);
      Core::JsonUtils::GetJsonValueString("RequestId", rootObject, requestId);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string DeleteMessageRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteMessageRequest &r) {
    os << "DeleteMessageRequest={region='" << r.region << "', queueUrl='" << r.queueUrl << "', receiptHandle='" << r.receiptHandle << "', resource='" << r.resource << "', requestId='" << r.requestId << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
