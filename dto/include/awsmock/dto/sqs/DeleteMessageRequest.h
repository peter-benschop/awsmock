//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_DELETEMESSAGEREQUEST_H
#define AWSMOCK_DTO_SQS_DELETEMESSAGEREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

namespace AwsMock::Dto::SQS {

    struct DeleteMessageRequest {

      /**
       * AWS region
       */
      std::string region;

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Receipt handle
       */
      std::string receiptHandle;

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
      friend std::ostream &operator<<(std::ostream &os, const DeleteMessageRequest &r) {
          os << "DeleteMessageRequest={region='" << r.region
             << "' queueUrl='" + r.queueUrl + "' receiptHandle='" + r.receiptHandle + "' resource='" + r.resource + "' requestId='" + r.requestId + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_DELETEMESSAGEREQUEST_H
