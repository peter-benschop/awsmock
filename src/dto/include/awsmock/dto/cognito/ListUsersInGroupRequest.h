//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_LIST_USER_IN_GROUP_REQUEST_H
#define AWSMOCK_DTO_COGNITO_LIST_USER_IN_GROUP_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief List users in a group request
     *
     * Example:
     * @code{.json}
     * {
     *   "GroupName": "string",
     *   "Limit": number,
     *   "NextToken": "string",
     *   "UserPoolId": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListUsersInGroupRequest : public Dto::Common::BaseRequest {

        /**
         * User pool ID
         */
        std::string userPoolId;

        /**
         * Name of the group
         */
        std::string groupName;

        /**
         * Limit
         */
        int limit;

        /**
         * Next token
         */
        std::string nextToken;

        /**
         * @brief Convert from a JSON object.
         *
         * @param payload json string object
         */
        void FromJson(const std::string &payload);

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const ListUsersInGroupRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_LIST_USER_IN_GROUP_REQUEST_H
