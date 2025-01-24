//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_UNTAG_QUEUE_REQUEST_H
#define AWSMOCK_DTO_SQS_UNTAG_QUEUE_REQUEST_H

// C++ standard includes
#include <string>
#include <vector>

// Awsmock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/StringUtils.h>

namespace AwsMock::Dto::SQS {

    struct UntagQueueRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Queue Url
         */
        std::string queueUrl;

        /**
         * Tags map
         */
        std::vector<std::string> tags;

        /**
         * @brief Converts the JSON string to a DTO
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * @brief Convert to JSON representation
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const UntagQueueRequest &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_UNTAG_QUEUE_REQUEST_H
