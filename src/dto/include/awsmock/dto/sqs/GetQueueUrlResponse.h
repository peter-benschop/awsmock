//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_GET_QUEUE_URL_RESPONSE_H
#define AWSMOCK_DTO_SQS_GET_QUEUE_URL_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/XML/XMLWriter.h"
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SQS {

    /**
     * Create queue response.
     *
     * Example:
     * @verbatim
     * <GetQueueUrlResponse xmlns="http://queue.amazonaws.com/doc/2012-11-05/">
     *     <GetQueueUrlResult>
     *         <QueueUrl>https://sqs.us-east-1.amazonaws.com/177715257436/MyQueue</QueueUrl>
     *     </GetQueueUrlResult>
     *     <ResponseMetadata>
     *         <RequestId>552d6f30-4c8e-5b32-aaed-33408c7d6c38</RequestId>
     *     </ResponseMetadata>
     * </GetQueueUrlResponse>
     * @endverbatim
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct GetQueueUrlResponse {

        /**
         * Name of the queue
         */
        std::string queueUrl;

        /**
         * Convert from XML representation
         *
         * @param xmlString  XML string
         */
        void FromXml(const std::string &xmlString);

        /**
         * Convert to XML representation
         *
         * @return XML string
         */
        [[nodiscard]] std::string ToXml() const;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        std::string ToJson() const;

        /**
         * Convert from JSON representation
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
        friend std::ostream &operator<<(std::ostream &os, const GetQueueUrlResponse &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_GET_QUEUE_URL_RESPONSE_H
