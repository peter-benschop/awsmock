//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/DeleteMessageBatchEntry.h>

namespace AwsMock::Dto::SQS {

  std::string DeleteMessageBatchEntry::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchEntry &d) {
    os << "DeleteMessageBatchEntry={id='" << d.id << "', receiptHandler='" + d.receiptHandle << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
