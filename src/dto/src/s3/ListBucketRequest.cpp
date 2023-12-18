//
// Created by vogje01 on 31/05/2023.
//

#include <awsmock/dto/s3/ListBucketRequest.h>

namespace AwsMock::Dto::S3 {

  std::string ListBucketRequest::ToString() const {
      std::stringstream ss;
      ss << (*this);
      return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListBucketRequest &r) {
      os << "ListBucketRequest={name='" << r.name << "' prefix='" << r.prefix << "' listType='" << r.listType << "' delimiter='" << r.delimiter
         << "' encodingType='" << r.encodingType << "'}";
      return os;
    }

} // namespace AwsMock::Dto::S3
