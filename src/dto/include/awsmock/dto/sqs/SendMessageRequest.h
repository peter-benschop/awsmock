//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_CREATEMESSAGEREQUEST_H
#define AWSMOCK_DTO_SQS_CREATEMESSAGEREQUEST_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/dto/sqs/MessageAttribute.h>

namespace AwsMock::Dto::SQS {

    struct SendMessageRequest {

      /**
       * Region
       */
      std::string region;

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Queue ARN
       */
      std::string queueArn;

      /**
       * Queue name
       */
      std::string queueName;

      /**
       * Message body
       */
      std::string body;

      /**
       * Message attributes
       */
      MessageAttributeList messageAttributes;

      /**
       * Request ID
       */
      std::string requestId;

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
      friend std::ostream &operator<<(std::ostream &os, const SendMessageRequest &r);

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_CREATEMESSAGEREQUEST_H
