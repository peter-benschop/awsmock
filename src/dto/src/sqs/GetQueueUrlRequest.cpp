//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/GetQueueUrlRequest.h>

namespace AwsMock::Dto::SQS {

  [[nodiscard]] std::string GetQueueUrlRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const GetQueueUrlRequest &r) {
    os << "GetQueueUrlRequest={region='" << r.region << "' queueName='" << r.queueName << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
