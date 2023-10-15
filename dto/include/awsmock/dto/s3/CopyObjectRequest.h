//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_COPYOBJECTREQUEST_H
#define AWSMOCK_CORE_DTO_COPYOBJECTREQUEST_H

// C++ standard includes
#include <map>
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
       * Metadata
       */
      std::map<std::string, std::string> metadata;
      
      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      std::string ToString() const;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const CopyObjectRequest &r);

    };

} // namespace AwsMock::Dto::S3

#endif // AWSMOCK_CORE_DTO_COPYOBJECTREQUEST_H
