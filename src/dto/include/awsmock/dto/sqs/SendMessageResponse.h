//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_SEND_MESSAGE_RESPONSE_H
#define AWSMOCK_DTO_SQS_SEND_MESSAGE_RESPONSE_H

// C++ standard includes
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/XML/XMLWriter.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/dto/sqs/MessageAttribute.h>

namespace AwsMock::Dto::SQS {

    /**
     * Send message response
     *
     * Example:
     * @verbatim
     * {
     *   "MD5OfMessageAttributes": "string",
     *   "MD5OfMessageBody": "string",
     *   "MD5OfMessageSystemAttributes": "string",
     *   "MessageId": "string",
     *   "SequenceNumber": "string"
     * }
     * @endverbatim
     */
    struct SendMessageResponse {

        /**
         * ID
         */
        long id;

        /**
         * Queue URL
         */
        std::string queueUrl;

        /**
         * Message ID
         */
        std::string messageId;

        /**
         * Receipt handle
         */
        std::string receiptHandle;

        /**
         * MD5 sum of body
         */
        std::string md5Body;

        /**
         * MD5 sum of sqs of user attributes
         */
        std::string md5UserAttr;

        /**
         * MD5 sum of sqs system attributes
         */
        std::string md5SystemAttr;

        /**
         * Message sequence number
         */
        std::string sequenceNumber = Poco::UUIDGenerator().createRandom().toString();

        /**
         * Request ID
         */
        std::string requestId;

        /**
         * Convert to JSON representation
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Convert from JSON representation
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * Convert to XML representation
         *
         * @return XML string
         */
        [[nodiscard]] std::string ToXml() const;

        /**
         * Convert from XML representation
         *
         * @param xmlString  XML string
         */
        void FromXml(const std::string &xmlString);

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
        friend std::ostream &operator<<(std::ostream &os, const SendMessageResponse &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_SEND_MESSAGE_RESPONSE_H
