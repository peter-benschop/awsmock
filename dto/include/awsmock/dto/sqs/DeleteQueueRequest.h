//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_DELETEQUEUEREQUEST_H
#define AWSMOCK_DTO_SQS_DELETEQUEUEREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/UUIDGenerator.h>

namespace AwsMock::Dto::SQS {

    struct DeleteQueueRequest {

      /**
       * AWS region
       */
      std::string region;

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Resource
       */
      std::string resource = "Unknown resource";

      /**
       * Request ID
       */
      std::string requestId = Poco::UUIDGenerator().createRandom().toString();

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
      friend std::ostream &operator<<(std::ostream &os, const DeleteQueueRequest &r);

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_DELETEQUEUEREQUEST_H
