//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/PutObjectRequest.h>

namespace AwsMock::Dto::S3 {

  std::string PutObjectRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const PutObjectRequest &r) {
    os << "PutObjectRequest={bucket='" << r.bucket << "', key='" << r.key << "', md5sum='" << r.md5Sum << "', contentType='" << r.contentType << "', contentLength='"
       << r.contentLength << "', owner='" << r.owner << "', region=' " << r.region << "', metadata={";
    for (const auto &m : r.metadata) {
      os << m.first << "=" << m.second << ", ";
    }
    os << '\b' << '\b' << "}}";
    return os;
  }

} // namespace AwsMock::Dto::s3
