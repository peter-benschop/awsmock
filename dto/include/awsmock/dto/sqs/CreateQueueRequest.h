//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_CREATEQUEUEREQUEST_H
#define AWSMOCK_DTO_SQS_CREATEQUEUEREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::SQS {

    struct CreateQueueRequest {

      /**
       * AWS region
       */
      std::string region;

      /**
       * Name
       */
      std::string name;

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Owner
       */
      std::string owner;

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
      friend std::ostream &operator<<(std::ostream &os, const CreateQueueRequest &r);

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_CREATEQUEUEREQUEST_H
