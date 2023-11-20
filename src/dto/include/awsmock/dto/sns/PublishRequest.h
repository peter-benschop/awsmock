//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_PUBLISHREQUEST_H
#define AWSMOCK_DTO_SNS_PUBLISHREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::SNS {

  struct PublishRequest {

    /**
     * Region
     */
    std::string region;

    /**
     * Topic ARN
     */
    std::string topicArn;

    /**
     * Target ARN
     */
    std::string targetArn;

    /**
     * Message body
     */
    std::string message;

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
    friend std::ostream &operator<<(std::ostream &os, const PublishRequest &r) {
      os << "PublishRequest={region='" + r.region + "' topicArn='" + r.topicArn + "' targetArn: '" + r.targetArn + "' message='" + r.message + "'}";
      return os;
    }
  };

} // namespace AwsMock::Dto::SNS

#endif // AWSMOCK_DTO_SNS_PUBLISHREQUEST_H
