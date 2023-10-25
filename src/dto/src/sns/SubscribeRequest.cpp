//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/SubscribeRequest.h>

namespace AwsMock::Dto::SNS {

  std::string SubscribeRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const SubscribeRequest &r) {
    os << "SubscribeRequest={region='" << r.region << "', topicArn='" << r.topicArn + "', owner='" << r.owner << "', protocol='" << r.protocol << "', endpoint='"
       << r.endpoint << "'}";
    return os;
  }
} // namespace AwsMock::Dto::SNS
