//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_PURGEQUEUEREQUEST_H
#define AWSMOCK_DTO_SQS_PURGEQUEUEREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// AwsMock includes
#include <awsmock/dto/common/Common.h>

namespace AwsMock::Dto::SQS {

    struct PurgeQueueRequest {

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * AWS region
       */
      std::string region;

      /**
       * Resource
       */
      std::string resource = "Unknown resource";

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
      friend std::ostream &operator<<(std::ostream &os, const PurgeQueueRequest &r) {
          os << "PurgeQueueRequest={queueUrl='" + r.queueUrl + "' region: '" + r.region + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_CREATEMESSAGEREQUEST_H
