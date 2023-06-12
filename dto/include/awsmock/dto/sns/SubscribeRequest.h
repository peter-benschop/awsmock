//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_SUBSCRIBEREQUEST_H
#define AWSMOCK_DTO_SNS_SUBSCRIBEREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::SNS {

    struct SubscribeRequest {

      /**
       * AWS region
       */
      std::string region;

      /**
       * Topic ARN
       */
      std::string topicArn;

      /**
       * Protocol
       */
      std::string protocol;

      /**
       * Endpoint
       */
      std::string endpoint;

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
      friend std::ostream &operator<<(std::ostream &os, const SubscribeRequest &r) {
          os << "SubscribeRequest={region='" + r.region + "' topicArn='" + r.topicArn + "' owner='" + r.owner + "' protocol='" + r.protocol +
              "' endpoint='" + r.endpoint + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SNS

#endif // AWSMOCK_DTO_SNS_SUBSCRIBEREQUEST_H
