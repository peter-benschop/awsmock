//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetMetadataResponse.h>

namespace AwsMock::Dto::S3 {

  std::string GetMetadataResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const GetMetadataResponse &r) {
    os << "GetMetadataResponse={bucket='" << r.bucket << "', key='" << r.key << "', md5sum='" << r.md5Sum << "', contentType='" << r.contentType << "', size=" << r.size << ", metadata={";
    for (const auto &m : r.metadata) {
      os << m.first << "=" << m.second << ", ";
    }
    os << "\b\b" << "}, created='" << Poco::DateTimeFormatter().format(r.created, Poco::DateTimeFormat::HTTP_FORMAT) << "', modified='" << Poco::DateTimeFormatter().format(r.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
    return os;
  }

} // namespace AwsMock::Dto::S3
