//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteMessageBatchRequest.h>

namespace AwsMock::Dto::SQS {

  std::string DeleteMessageBatchRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchRequest &r) {
    os << "DeleteMessageBatchRequest={region='" << r.region
       << "' queueUrl='" + r.queueUrl + "' entries={";
    for (const auto &entry : r.deleteMessageBatchEntries) {
      os << entry.ToString() << ",";
    }
    os << "\b\b" << "}}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
