//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/Owner.h>

namespace AwsMock::Dto::S3 {

  std::string Owner::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Owner &o) {
    os << "Owner={userPoolId='" << o.id << "', displayName='" << o.displayName << "'}";
    return os;
  }

} // namespace AwsMock::Dto::S3
