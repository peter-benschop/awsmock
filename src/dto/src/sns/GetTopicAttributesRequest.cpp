//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/GetTopicAttributesRequest.h>

namespace AwsMock::Dto::SNS {

  std::string GetTopicAttributesRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const GetTopicAttributesRequest &r) {
    os << "GetTopicAttributesRequest={region='" << r.region << "', topicArn='" << r.topicArn << "'}";
    return os;
  }

} // namespace AwsMock::Dto::SNS
