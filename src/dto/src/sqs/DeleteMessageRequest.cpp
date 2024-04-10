//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteMessageRequest.h>

namespace AwsMock::Dto::SQS {

  std::string DeleteMessageRequest::ToJson() const {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("QueueUrl", queueUrl);
      rootJson.set("ReceiptHandle", receiptHandle);
      rootJson.set("RequestId", requestId);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

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
    os << "DeleteMessageRequest=" << r.ToJson();
    return os;
  }

} // namespace AwsMock::Dto::SQS
