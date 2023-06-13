//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTEREQUEST_H
#define AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTEREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

namespace AwsMock::Dto::SQS {

    struct GetQueueAttributesRequest {

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Attribute names list
       */
      std::vector<std::string> attributeNames;

      /**
       * Resource
       */
      std::string resource = "SQS";

      /**
       * Resource
       */
      std::string requestId = Poco::UUIDGenerator().createRandom().toString();

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
      friend std::ostream &operator<<(std::ostream &os, const GetQueueAttributesRequest &r) {
          os << "GetQueueAttributesRequest={queueUrl='" + r.queueUrl + "' resource='" + r.resource + "' requestId='" + r.requestId + "' attributeNames=[";
          for(const auto &it : r.attributeNames) {
              os << it;
          }
          os << "]}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTEREQUEST_H
