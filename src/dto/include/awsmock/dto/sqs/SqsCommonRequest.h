//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_COMMON_REQUEST_H
#define AWSMOCK_DTO_SQS_COMMON_REQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::SQS {

  struct SqsCommonRequest {

    /**
     * AWS region
     */
    std::string region;

    /**
     * AWS request ID
     */
    std::string requestId;

    /**
     * Converts the JSON string to DTO.
     *
     * @param jsonString JSON string
     */
    void FromJson(const std::string &jsonString);

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
    friend std::ostream &operator<<(std::ostream &os, const SqsCommonRequest &r);

  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_COMMON_REQUEST_H
