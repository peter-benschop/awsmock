//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_UNSUBSCRIBEREQUEST_H
#define AWSMOCK_DTO_SNS_UNSUBSCRIBEREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::SNS {

    struct UnsubscribeRequest {

      /**
       * AWS region
       */
      std::string region;

      /**
       * Subscription ARN
       */
      std::string subscriptionArn;

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const ;

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const UnsubscribeRequest &r);

    };

} // namespace AwsMock::Dto::SNS

#endif // AWSMOCK_DTO_SNS_UNSUBSCRIBEREQUEST_H
