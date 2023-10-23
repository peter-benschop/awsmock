//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/s3/GetObjectResponse.h>

namespace AwsMock::Dto::S3 {

  std::string GetObjectResponse::ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      std::ostream &operator<<(std::ostream &os, const GetObjectResponse &r) {
          os << "GetObjectResponse={bucket='" << r.bucket << "', key='" << r.key << "', size='" << r.size << "', filename='" << r.filename << "', contentType='"
             << r.contentType << "', metadata={";
          for (const auto &m : r.metadata) {
              os << m.first << "=" << m.second << ", ";
          }
          os << '\b' << '\b' << "' created='" << Poco::DateTimeFormatter().format(r.created, Poco::DateTimeFormat::HTTP_FORMAT) <<
             "', modified='" << Poco::DateTimeFormatter().format(r.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
          return os;
      }

} // namespace AwsMock::Dto::S3
