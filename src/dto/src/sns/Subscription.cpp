//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/Subscription.h>

namespace AwsMock::Dto::SNS {

  std::string Subscription::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Subscription &r) {
    os << "Subscription={region='" << r.region << "', topicArn='" << r.topicArn + "', owner='" << r.owner << "', protocol='" << r.protocol << "', endpoint='"
       << r.endpoint << "'}";
    return os;
  }
} // namespace AwsMock::Dto::SNS
