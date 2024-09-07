//
// Created by vogje01 on 8/23/24.
//

#ifndef AWSMOCK_DTO_SQS_MESSAGE_ENTRY_FAILED_H
#define AWSMOCK_DTO_SQS_MESSAGE_ENTRY_FAILED_H

// C++ includes
#include <map>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/sqs/model/MessageAttribute.h>

namespace AwsMock::Dto::SQS {

    /**
     * @brief SQS message entry failed
     *
     * @code{.json}
     * {
     *   "Code": "string",
     *   "Id": "string",
     *   "Message": "string",
     *   "SenderFault": boolean
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct MessageFailed {

        /**
         * Error code
         */
        std::string code;

        /**
         * Message ID
         */
        std::string id;

        /**
         * Message
         */
        std::string message;

        /**
         * Sender fault
         */
        bool senderFault;

        /**
         * @brief Converts the DTO to a JSON string.
         *
         * @return DTO as JSON string.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * @brief Converts a JSON representation to s DTO.
         *
         * @param object JSON object.
         */
        void FromJson(const Poco::JSON::Object::Ptr &object);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const MessageFailed &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_MESSAGE_ENTRY_FAILED_H
