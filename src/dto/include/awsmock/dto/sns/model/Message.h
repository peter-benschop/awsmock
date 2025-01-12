//
// Created by vogje01 on 10/9/24.
//

#ifndef AWSMOCK_DTO_SNS_MESSAGE_H
#define AWSMOCK_DTO_SNS_MESSAGE_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SNS {

    struct Message {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Topic ARM
         */
        std::string topicArn;

        /**
         * Message ID
         */
        std::string messageId;

        /**
         * Message
         */
        std::string message;

        /**
         * Creation time
         */
        system_clock::time_point created;

        /**
         * Modification time
         */
        system_clock::time_point modified;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

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
        friend std::ostream &operator<<(std::ostream &os, const Message &r);
    };
}// namespace AwsMock::Dto::SNS
#endif//AWSMOCK_DTO_SNS_MESSAGE_H
