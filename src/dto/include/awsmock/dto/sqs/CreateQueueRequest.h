//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_CREATE_QUEUE_REQUEST_H
#define AWSMOCK_DTO_SQS_CREATE_QUEUE_REQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <map>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/dto/sqs/QueueAttribute.h>
#include <awsmock/dto/sqs/SqsCommonRequest.h>

namespace AwsMock::Dto::SQS {

  struct CreateQueueRequest {

    /**
     * AWS region
     */
    std::string region;

    /**
     * Queue name
     */
    std::string queueName;

    /**
     * Queue URL
     */
    std::string queueUrl;

    /**
     * Owner
     */
    std::string owner;

    /**
     * Attributes
     */
    QueueAttributeList attributes;

    /**
     * Tags
     */
    std::map<std::string, std::string> tags;

    /**
     * AWS request ID
     */
    std::string requestId;

    /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson() const;

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
    friend std::ostream &operator<<(std::ostream &os, const CreateQueueRequest &r);

  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_CREATE_QUEUE_REQUEST_H
