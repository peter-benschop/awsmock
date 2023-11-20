//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_GETQUEUEURLREQUEST_H
#define AWSMOCK_DTO_SQS_GETQUEUEURLREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::SQS {

  struct GetQueueUrlRequest {

    /**
     * AWS region name
     */
    std::string region;

    /**
     * Name of the queue
     */
    std::string queueName;

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
    friend std::ostream &operator<<(std::ostream &os, const GetQueueUrlRequest &r);

  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_GETQUEUEURLREQUEST_H
