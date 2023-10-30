//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetMetadataRequest.h>

namespace AwsMock::Dto::S3 {

  std::string GetMetadataRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const GetMetadataRequest &r) {
    os << "GetMetadataRequest={region='" << r.region << " bucket='" << r.bucket << "' key='" << r.key << "'}";
    return os;
  }

} // namespace AwsMock::Dto::S3
