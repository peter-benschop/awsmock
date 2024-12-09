//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_GET_QUEUE_ATTRIBUTE_RESPONSE_H
#define AWSMOCK_DTO_SQS_GET_QUEUE_ATTRIBUTE_RESPONSE_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::SQS {

    struct GetQueueAttributesResponse {

        /**
         * Attributes
         */
        std::vector<std::pair<std::string, std::string>> attributes;

        /**
         * Resource
         */
        std::string resource = "SQS";

        /**
         * Resource
         */
        std::string requestId = Core::StringUtils::CreateRandomUuid();

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert to XML representation
         *
         * @return XML string
         */
        [[nodiscard]] std::string ToXml() const;

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
        friend std::ostream &operator<<(std::ostream &os, const GetQueueAttributesResponse &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_GET_QUEUE_ATTRIBUTE_RESPONSE_H
