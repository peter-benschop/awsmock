//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteQueueRequest.h>

namespace AwsMock::Dto::SQS {

  std::string DeleteQueueRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteQueueRequest &r) {
    os << "DeleteQueueRequest={queueUrl='" + r.queueUrl + "' resource='" + r.resource + "' requestId='" + r.requestId + "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
