//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_CREATE_QUEUE_RESPONSE_H
#define AWSMOCK_DTO_SQS_CREATE_QUEUE_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::SQS {

    struct CreateQueueResponse {

        /**
         * Region
         */
        std::string region;

        /**
         * Name
         */
        std::string name;

        /**
         * Owner
         */
        std::string owner;

        /**
         * Queue URL
         */
        std::string queueUrl;

        /**
         * Queue ARN
         */
        std::string queueArn;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert from JSON representation
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

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
        friend std::ostream &operator<<(std::ostream &os, const CreateQueueResponse &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_CREATE_QUEUE_RESPONSE_H
