//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_GETOBJECTRESPONSE_H
#define AWSMOCK_DTO_S3_GETOBJECTRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <map>

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
       * Metadata
       */
      std::map<std::string, std::string> metadata;

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
      [[nodiscard]] std::string ToString() const;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const GetObjectResponse &r);

    };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_DTO_S3_GETOBJECTRESPONSE_H
