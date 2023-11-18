//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SetVisibilityTimeoutRequest.h>

namespace AwsMock::Dto::SQS {

  std::string SetVisibilityTimeoutRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SetVisibilityTimeoutRequest &r) {
    os << "SetVisibilityTimeoutRequest={region='" << r.region << "', queueUrl='" << r.queueUrl << "', visibilityTimeout=" << r.visibilityTimeout << " requestId='" + r.requestId + "', receiptHandle='" << r.receiptHandle << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
