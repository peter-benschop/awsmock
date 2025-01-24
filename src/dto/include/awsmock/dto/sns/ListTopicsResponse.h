//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_LIST_TOPICS_RESPONSE_H
#define AWSMOCK_DTO_SQS_LIST_TOPICS_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/entity/sns/Topic.h>

namespace AwsMock::Dto::SNS {

    struct ListTopicsResponse {

        /**
         * List of topics
         */
        Database::Entity::SNS::TopicList topicList;

        /**
         * Next token
         */
        std::string nextToken;

        /**
         * Total number of queue
         */
        long total;

        /**
         * @brief Convert to JSON representation
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
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const ListTopicsResponse &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SQS_LIST_TOPICS_RESPONSE_H
