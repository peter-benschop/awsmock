//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_DELETEMESSAGEBATCHREQUEST_H
#define AWSMOCK_DTO_SQS_DELETEMESSAGEBATCHREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

// AwsMock includes
#include <awsmock/dto/sqs/DeleteMessageBatchEntry.h>

namespace AwsMock::Dto::SQS {

    struct DeleteMessageBatchRequest {

      /**
       * AWS region
       */
      std::string region;

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Entries
       */
      DeleteMessageBatchEntries deleteMessageBatchEntries;

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
      [[nodiscard]] std::string ToString() const;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchRequest &r);

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_DELETEMESSAGEBATCHREQUEST_H
