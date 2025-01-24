//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_RECEIVE_MESSAGE_RESPONSE_H
#define AWSMOCK_DTO_SQS_RECEIVE_MESSAGE_RESPONSE_H

// C++ standard includes
#include <string>

// Boost includes
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

// AwsMock includes
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/dto/sqs/model/MessageAttribute.h>
#include <awsmock/entity/sqs/Message.h>

namespace AwsMock::Dto::SQS {

    /**
     * Receive message response.
     *
     * Example:
     * @code{.json}
     * {
     *   "resources": [
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
     * }
     * @endcode
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
         * List of attribute
         */
        std::map<std::string, std::string> attributes;

        /**
         * List of message attribute names
         */
        std::map<std::string, MessageAttribute> messageAttributes;

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
        [[nodiscard]] std::string ToString();

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, ReceiveMessageResponse &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_RECEIVE_MESSAGE_RESPONSE_H
