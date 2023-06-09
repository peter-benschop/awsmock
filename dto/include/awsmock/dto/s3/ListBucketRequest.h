//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LISTBUCKETREQUEST_H
#define AWSMOCK_DTO_S3_LISTBUCKETREQUEST_H

// C++ Standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::S3 {

    struct ListBucketRequest {

      /**
       * Name
       */
      std::string name;

      /**
       * Prefix
       */
      std::string prefix;

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const ListBucketRequest &r) {
          os << "ListBucketRequest={name='" + r.name + "' prefix='" + r.prefix + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_DTO_S3_LISTBUCKETREQUEST_H
