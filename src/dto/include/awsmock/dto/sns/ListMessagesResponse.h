//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_LIST_MESSAGES_RESPONSE_H
#define AWSMOCK_DTO_SNS_LIST_MESSAGES_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/entity/sns/Message.h>

namespace AwsMock::Dto::SNS {

    /**
     * @brief List messages response
     *
     * @par
     * This is not an AWS SDK response, but only available in awsmock
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListMessagesResponse {

        /**
         * List of topics
         */
        std::vector<Database::Entity::SNS::Message> messageList;

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
        friend std::ostream &operator<<(std::ostream &os, const ListMessagesResponse &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SQS_LIST_TOPICS_RESPONSE_H
