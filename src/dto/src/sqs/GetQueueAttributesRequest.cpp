//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/sqs/GetQueueAttributesRequest.h>

namespace AwsMock::Dto::SQS {

  std::string GetQueueAttributesRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const GetQueueAttributesRequest &r) {
    os << "GetQueueAttributesRequest={region='" << r.region
       << "' queueUrl='" + r.queueUrl + "' resource='" + r.resource + "' requestId='" + r.requestId + "' attributeNames=[";
    for (const auto &it : r.attributeNames) {
      os << it;
    }
    os << "]}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
