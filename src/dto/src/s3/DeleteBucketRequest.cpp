//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteBucketRequest.h>

namespace AwsMock::Dto::S3 {

  std::string DeleteBucketRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteBucketRequest &r) {
    os << "DeleteObjectRequest={region='" << r.region << "', user='" << r.user << "', bucket='" << r.bucket << "'}";
    return os;
  }

} // namespace AwsMock::Dto::S3
