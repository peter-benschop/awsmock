//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_GETMETADATAREQUEST_H
#define AWSMOCK_DTO_S3_GETMETADATAREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

    struct GetMetadataRequest {

      /**
       * Bucket
       */
      std::string bucket;

      /**
       * Key
       */
      std::string key;

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
      friend std::ostream &operator<<(std::ostream &os, const GetMetadataRequest &r) {
          os << "GetMetadataRequest={bucket='" + r.bucket + "' key='" + r.key + "'}";
          return os;
      }
    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_DTO_S3_GETMETADATAREQUEST_H
