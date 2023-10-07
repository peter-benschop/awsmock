//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sqs/ReceiveMessageRequest.h>

namespace AwsMock::Dto::SQS {

  std::string ReceiveMessageRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ReceiveMessageRequest &r) {
    os << "ReceiveMessageRequest={region='" + r.region + "' queueUrl='" + r.queueUrl + "' maxMessages='" + std::to_string(r.maxMessages) +
        "' visibility='" + std::to_string(r.visibility) + "' waitTimeSeconds='" + std::to_string(r.waitTimeSeconds) + "' resource='" + r.resource +
        "' requestId: '" + r.requestId + "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
