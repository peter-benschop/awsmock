//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/sqs/SetQueueAttributesRequest.h>

namespace AwsMock::Dto::SQS {

  std::string SetQueueAttributesRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SetQueueAttributesRequest &r) {
    os << "SetQueueAttributesRequest={queueUrl='" << r.queueUrl + "', resource='" << r.resource + "', requestId='" << r.requestId << "', attributes={";
    for (auto &attribute : r.attributes) {
      os << attribute.first << "='" << attribute.second << "', ";
    }
    os << "\b\b" << "}}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
