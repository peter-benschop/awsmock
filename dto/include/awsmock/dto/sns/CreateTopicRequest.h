//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_CREATETOPICREQUEST_H
#define AWSMOCK_DTO_SQS_CREATETOPICREQUEST_H

// C++ standard includes
#include <string>

namespace AwsMock::Dto::SNS {

    struct CreateTopicRequest {

      /**
       * AWS region
       */
      std::string region;

      /**
       * Name
       */
      std::string topicName;

      /**
       * Owner
       */
      std::string owner;

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
      friend std::ostream &operator<<(std::ostream &os, const CreateTopicRequest &r) {
          os << "CreateTopicRequest={region='" + r.region + "' topicName='" + r.topicName + "' owner='" + r.owner + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SNS

#endif // AWSMOCK_DTO_SQS_CREATETOPICREQUEST_H
