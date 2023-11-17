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
    os << "ReceiveMessageRequest={region='" << r.region << "', queueUrl='" << r.queueUrl << "', queueName='" << r.queueName << "', maxMessages='" << r.maxMessages << "', visibility='" << r.visibility << "', waitTimeSeconds='" << r.waitTimeSeconds
       << "', resource='" << r.resource << "', requestId: '" << r.requestId << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
