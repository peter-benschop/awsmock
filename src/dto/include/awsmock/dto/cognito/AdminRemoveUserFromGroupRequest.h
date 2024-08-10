//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_ADMIN_REMOVE_USER_FROM_GROUP_REQUEST_H
#define AWSMOCK_DTO_COGNITO_ADMIN_REMOVE_USER_FROM_GROUP_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/cognito/model/MessageAction.h>
#include <awsmock/dto/cognito/model/UserAttribute.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Removes a user from a group
     *
     * Exanple:
     * @code{.json}
     * {
     *   "GroupName": "string",
     *   "Username": "string",
     *   "UserPoolId": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct AdminRemoveUserFromGroupRequest : public Dto::Common::BaseRequest {

        /**
         * Name of the group
         */
        std::string groupName;

        /**
         * Name of the user
         */
        std::string userName;

        /**
         * User pool id
         */
        std::string userPoolId;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert from a JSON object.
         *
         * @param payload json string object
         */
        void FromJson(const std::string &payload);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @param r request
         * @param os output stream
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const AdminRemoveUserFromGroupRequest &r);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_ADMIN_REMOVE_USER_FROM_GROUP_REQUEST_H
