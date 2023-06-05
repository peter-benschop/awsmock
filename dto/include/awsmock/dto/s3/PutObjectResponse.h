//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_PUTOBJECTRESPONSE_H
#define AWSMOCK_CORE_DTO_PUTOBJECTRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

    struct PutObjectResponse {

      /**
       * Bucket
       */
      std::string bucket;

      /**
       * Key
       */
      std::string key;

      /**
       * ETag
       */
      std::string etag;

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
      friend std::ostream &operator<<(std::ostream &os, const PutObjectResponse &p) {
            os << "PutObjectResponse={bucket='" + p.bucket + "' key='" + p.key + "' etag='" + p.etag + "''}";
            return os;
      }

    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_CORE_DTO_PUTOBJECTRESPONSE_H
