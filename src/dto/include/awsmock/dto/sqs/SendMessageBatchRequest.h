//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_SEND_MESSAGE_BATCH_REQUEST_H
#define AWSMOCK_DTO_SQS_SEND_MESSAGE_BATCH_REQUEST_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/dto/sqs/SqsCommonRequest.h>
#include <awsmock/dto/sqs/model/MessageAttribute.h>
#include <awsmock/dto/sqs/model/MessageEntry.h>

namespace AwsMock::Dto::SQS {

    /**
     * @brief Send message batch request
     *
     * Example (from Java v2 client):
     * @code{.json}
     * {
     *   "Entries": [
     *      {
     *         "DelaySeconds": number,
     *         "Id": "string",
     *         "MessageAttributes": {
     *            "string" : {
     *               "BinaryListValues": [ blob ],
     *               "BinaryValue": blob,
     *               "DataType": "string",
     *               "StringListValues": [ "string" ],
     *               "StringValue": "string"
     *            }
     *         },
     *         "MessageBody": "string",
     *         "MessageDeduplicationId": "string",
     *         "MessageGroupId": "string",
     *         "MessageSystemAttributes": {
     *            "string" : {
     *               "BinaryListValues": [ blob ],
     *               "BinaryValue": blob,
     *               "DataType": "string",
     *               "StringListValues": [ "string" ],
     *               "StringValue": "string"
     *            }
     *         }
     *      }
     *   ],
     *   "QueueUrl": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct SendMessageBatchRequest {

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
        std::vector<MessageEntry> entries;

        /**
         * Request ID
         */
        std::string requestId;

        /**
         * Converts the JSON string to a DTO
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, SendMessageBatchRequest &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_SEND_MESSAGE_BATCH_REQUEST_H
