//
// Created by vogje01 on 02/10/2023.
//

#include <awsmock/dto/sqs/PurgeQueueRequest.h>

namespace AwsMock::Dto::SQS {

  std::string PurgeQueueRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const PurgeQueueRequest &r) {
    os << "PurgeQueueRequest={queueUrl='" + r.queueUrl + "' region: '" + r.region + "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
