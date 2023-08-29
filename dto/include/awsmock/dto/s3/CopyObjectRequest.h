//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_COPYOBJECTREQUEST_H
#define AWSMOCK_CORE_DTO_COPYOBJECTREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::S3 {

    struct CopyObjectRequest {

      /**
       * Region
       */
      std::string region;

      /**
       * Region
       */
      std::string user;

      /**
       * Source bucket
       */
      std::string sourceBucket;

      /**
       * Source key
       */
      std::string sourceKey;

      /**
       * Target bucket
       */
      std::string targetBucket;

      /**
       * Target key
       */
      std::string targetKey;

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
      friend std::ostream &operator<<(std::ostream &os, const CopyObjectRequest &r) {
          os << "CopyObjectRequest={region='" + r.region + "' user='" + r.user + "' sourceBucket='" + r.sourceBucket + "' sourceKey='" + r.sourceKey
              + "' targetBucket='" + r.targetBucket + "' targetKey='" + r.targetKey + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::S3

#endif // AWSMOCK_CORE_DTO_COPYOBJECTREQUEST_H
