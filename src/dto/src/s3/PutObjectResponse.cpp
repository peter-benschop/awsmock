//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/PutObjectResponse.h>

namespace AwsMock::Dto::S3 {

  std::string PutObjectResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const PutObjectResponse &p) {
    os << "PutObjectResponse={bucket='" << p.bucket << "', key='" << p.key << "', etag='" << p.etag << "', contentLength: " << p.contentLength << ", versionId='" << p.versionId << "', sha1sum='" << p.checksumSha1 << "', sha256sum='" << p.checksumSha256
       << "',metadata={";
    for (const auto &m : p.metadata) {
      os << m.first << "=" << m.second << ", ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "]}";
    return os;
  }

}