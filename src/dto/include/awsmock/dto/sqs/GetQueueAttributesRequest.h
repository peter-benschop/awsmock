//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_GET_QUEUE_ATTRIBUTE_REQUEST_H
#define AWSMOCK_DTO_SQS_GET_QUEUE_ATTRIBUTE_REQUEST_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::SQS {

    struct GetQueueAttributesRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Queue URL
         */
        std::string queueUrl;

        /**
         * UserAttribute names list
         */
        std::vector<std::string> attributeNames;

        /**
         * Resource
         */
        std::string resource = "SQS";

        /**
         * Resource
         */
        std::string requestId = Core::StringUtils::CreateRandomUuid();

        /**
         * @brief Converts the JSON string to a DTO
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * @brief Converts the JSON string to a DTO
         *
         * @return JSON string
         */
        std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const GetQueueAttributesRequest &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_GET_QUEUE_ATTRIBUTE_REQUEST_H
