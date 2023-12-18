//
// Created by vogje01 on 12/18/23.
//

#include <awsmock/dto/s3/Content.h>

namespace AwsMock::Dto::S3 {

  std::string Content::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const Content &c) {
    os << "Content={etag='" << c.etag << "'. key='" << c.key << "', owner='" << c.owner << "', size='" << c.size << "', storageClass='" << c.storageClass << "', checksumAlgorithms=[";
    for (const auto &algorithm : c.checksumAlgorithms) {
      os << "'" << algorithm << ", ";
    }
    os << "], lastModified='" << c.lastModified << "'}";
    return os;
  }

} // namespace AwsMock::Dto::S3
