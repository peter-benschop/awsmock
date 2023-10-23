//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetObjectRequest.h>

namespace AwsMock::Dto::S3 {

  std::string GetObjectRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const GetObjectRequest &r) {
    os << "GetObjectRequest={region='" << r.region << ", bucket='" << r.bucket << "' key='" << r.key << "', versionId='" << r.versionId << "'}";
    return os;
  }

} // namespace AwsMock::Dto::S3
