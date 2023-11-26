//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/ChangeMessageVisibilityRequest.h>

namespace AwsMock::Dto::SQS {

  void ChangeMessageVisibilityRequest::FromJson(const std::string &jsonString) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    auto rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      // Attributes
      Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);
      Core::JsonUtils::GetJsonValueString("ReceiptHandle", rootObject, receiptHandle);
      Core::JsonUtils::GetJsonValueInt("VisibilityTimeout", rootObject, visibilityTimeout);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string ChangeMessageVisibilityRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ChangeMessageVisibilityRequest &r) {
    os << "ChangeMessageVisibilityRequest={region='" << r.region << "', queueUrl='" << r.queueUrl << "', visibilityTimeout=" << r.visibilityTimeout << " requestId='" + r.requestId + "', receiptHandle='" << r.receiptHandle << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
