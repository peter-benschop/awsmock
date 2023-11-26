//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_RECEIVEMESSAGERESPONSE_H
#define AWSMOCK_DTO_SQS_RECEIVEMESSAGERESPONSE_H

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
#include <Poco/JSON/Object.h>
#include <Poco/XML/XMLWriter.h>

// AwsMock includes
#include <awsmock/entity/sqs/Message.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SQS {

  /**
   * Receive message response.
   * <p>
   * Example:
   * <pre>
   * {
   *   "messages": [
   *      {
   *         "Attributes": {
   *            "string" : "string"
   *         },
   *         "Body": "string",
   *         "MD5OfBody": "string",
   *         "MD5OfMessageAttributes": "string",
   *         "MessageAttributes": {
   *            "string" : {
   *               "BinaryListValues": [ blob ],
   *               "BinaryValue": blob,
   *               "DataType": "string",
   *               "StringListValues": [ "string" ],
   *               "StringValue": "string"
   *            }
   *         },
   *         "MessageId": "string",
   *         "ReceiptHandle": "string"
   *      }
   *   ]
   *   }
   * <pre>
   */
  struct ReceiveMessageResponse {

    /**
     * Message list
     */
    Database::Entity::SQS::MessageList messageList;

    /**
     * Resource
     */
    std::string resource = "SQS";

    /**
     * Resource
     */
    std::string requestId;

    /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson();

    /**
     * Convert to XML representation
     *
     * @return XML string
     */
    [[nodiscard]] std::string ToXml() const;
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
    friend std::ostream &operator<<(std::ostream &os, const ReceiveMessageResponse &r);

  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_RECEIVEMESSAGERESPONSE_H
