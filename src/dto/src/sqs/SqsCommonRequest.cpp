//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SqsCommonRequest.h>

namespace AwsMock::Dto::SQS {

  std::string SqsCommonRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SqsCommonRequest &r) {
    os << "SqsCommonRequest={region='" << r.region << "', requestId='" << r.requestId << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
