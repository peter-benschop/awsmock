//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/CreateQueueRequest.h>

namespace AwsMock::Dto::SQS {

  std::string CreateQueueRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateQueueRequest &r) {
    os << "CreateQueueRequest={region='" << r.region << "' queueUrl='" << r.queueUrl << "' name='" << r.name << "' owner='" << r.owner << "', attributes={";
    for (auto &attribute : r.attributes) {
      os << attribute.attributeName << "='" << attribute.attributeValue << "', ";
    }
    os << "\b\b" << "}, tags={";
    for (auto &tag : r.tags) {
      os << tag.first << "='" << tag.second << "', ";
    }
    os << "\b\b" << "}}";
    return os;
  }

} // namespace AwsMock::Dto::SQS
