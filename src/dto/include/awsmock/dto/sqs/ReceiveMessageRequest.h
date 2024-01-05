//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_RECEIVE_MESSAGE_REQUEST_H
#define AWSMOCK_DTO_SQS_RECEIVE_MESSAGE_REQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Text.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/XML/XMLWriter.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/entity/sqs/Message.h>

namespace AwsMock::Dto::SQS {

  /**
   * Receive message request.
   * <p>
   * Example:
   * <pre>
   * {
   *   "AttributeNames": [ "string" ],
   *   "MaxNumberOfMessages": number,
   *   "MessageAttributeNames": [ "string" ],
   *   "MessageSystemAttributeNames": [ "string" ],
   *   "QueueUrl": "string",
   *   "ReceiveRequestAttemptId": "string",
   *   "VisibilityTimeout": number,
   *   "WaitTimeSeconds": number
   * }
   * </pre>
   */
  struct ReceiveMessageRequest {

    /**
     * AWS region
     */
    std::string region;

    /**
     * Queue URL
     */
    std::string queueUrl;

    /**
     * Queue name
     */
    std::string queueName;

    /**
     * Maximal number of messages
     */
    int maxMessages = 10;

    /**
     * Visibility
     */
    int visibilityTimeout = 15;

    /**
     * Wait time in seconds
     */
    int waitTimeSeconds = 1;

    /**
     * MessageAttribute names
     */
    std::vector<std::string> AttributeName = {"All"};

    /**
     * Resource
     */
    std::string resource = "SQS";

    /**
     * Resource
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
     * @return DTO as string
     */
    [[nodiscard]] std::string ToString() const;

    /**
     * Stream provider.
     *
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const ReceiveMessageRequest &r);

  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_RECEIVE_MESSAGE_REQUEST_H
