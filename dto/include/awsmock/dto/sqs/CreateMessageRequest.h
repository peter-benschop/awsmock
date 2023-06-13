//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_CREATEMESSAGEREQUEST_H
#define AWSMOCK_DTO_SQS_CREATEMESSAGEREQUEST_H

// C++ standard includes
#include <string>

namespace AwsMock::Dto::SQS {

    struct CreateMessageRequest {

      /**
       * Region
       */
      std::string region;

      /**
       * Queue URL
       */
      std::string url;

      /**
       * Message body
       */
      std::string body;

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
      friend std::ostream &operator<<(std::ostream &os, const CreateMessageRequest &r) {
          os << "CreateMessageRequest={region='" + r.region + "' url='" + r.url + "' body: '" + r.body + "'}";
          return os;
      }
    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_CREATEMESSAGEREQUEST_H
