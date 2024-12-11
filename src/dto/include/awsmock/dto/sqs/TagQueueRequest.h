//
// Created by vogje01 on 22/012/2023.
//

#ifndef AWSMOCK_DTO_SQS_TAG_QUEUE_REQUEST_H
#define AWSMOCK_DTO_SQS_TAG_QUEUE_REQUEST_H

// C++ standard includes
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::SQS {

    struct TagQueueRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Queue URL
         */
        std::string queueUrl;

        /**
         * Tags map
         */
        std::map<std::string, std::string> tags;

        /**
         * @brief Converts the JSON string to a DTO
         *
         * @return JSON string
         */
        std::string ToJson() const;

        /**
         * @brief Converts the JSON string to a DTO
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

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
        friend std::ostream &operator<<(std::ostream &os, const TagQueueRequest &r);
    };

    typedef std::map<std::string, std::string> TagList;

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_TAG_QUEUE_REQUEST_H
