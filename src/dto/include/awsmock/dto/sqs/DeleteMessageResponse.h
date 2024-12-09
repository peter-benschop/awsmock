//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_DELETE_MESSAGE_RESPONSE_H
#define AWSMOCK_DTO_SQS_DELETE_MESSAGE_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::SQS {

    struct DeleteMessageResponse {

        /**
         * Resource
         */
        std::string resource = "SQS";

        /**
         * Resource
         */
        std::string requestId = Core::StringUtils::CreateRandomUuid();

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const DeleteMessageResponse &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_DELETE_MESSAGE_RESPONSE_H
