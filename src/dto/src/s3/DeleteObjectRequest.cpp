//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/DeleteObjectRequest.h>

namespace AwsMock::Dto::S3 {

  std::string DeleteObjectRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteObjectRequest &r) {
    os << "DeleteObjectRequest={region='" + r.region + "' user='" + r.user + "' bucket='" + r.bucket + "' key='" + r.key + "'}";
    return os;
  }

} // namespace AwsMock::Dto::S3
