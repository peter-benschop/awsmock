//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_GETOBJECTRESPONSE_H
#define AWSMOCK_CORE_DTO_GETOBJECTRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

namespace AwsMock::Dto::S3 {

    struct GetObjectResponse {

      /**
       * Bucket
       */
      std::string bucket;

      /**
       * Key
       */
      std::string key;

      /**
       * Content length
       */
      long size;

      /**
       * File name
       */
      std::string filename;

      /**
       * Content type
       */
      std::string contentType;

      /**
       * Created
       */
      Poco::DateTime created;

      /**
       * Modified
       */
      Poco::DateTime modified;

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
      friend std::ostream &operator<<(std::ostream &os, const GetObjectResponse &r) {
          os << "GetObjectResponse={bucket='" + r.bucket + "' key='" + r.key + "' size='"+ std::to_string(r.size) + "' filename='" + r.filename  +
          "' contentType='"+ r.contentType + "' created='" + Poco::DateTimeFormatter().format(r.created, Poco::DateTimeFormat::HTTP_FORMAT) +
          "' modified='" + Poco::DateTimeFormatter().format(r.modified, Poco::DateTimeFormat::HTTP_FORMAT) +"'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_CORE_DTO_GETOBJECTRESPONSE_H
