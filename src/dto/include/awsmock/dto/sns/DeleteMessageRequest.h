//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_DELETE_MESSAGE_REQUEST_H
#define AWSMOCK_DTO_SNS_DELETE_MESSAGE_REQUEST_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::SNS {

    /**
     * @brief Delete message request.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct DeleteMessageRequest {

        /**
         * Topic ARN
         */
        std::string topicArn;

        /**
         * Message Id
         */
        std::string messageId;

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
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const DeleteMessageRequest &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_DELETE_MESSAGE_REQUEST_H
