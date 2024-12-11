//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_LIST_USERS_IN_GROUP_RESPONSE_H
#define AWSMOCK_DTO_COGNITO_LIST_USERS_IN_GROUP_RESPONSE_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/cognito/model/User.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief List users in a group response
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListUsersInGroupResponse : Common::BaseRequest {

        /**
         * User pool entities
         */
        std::vector<User> users;

        /**
         * @brief Convert to a JSON string.
         *
         * @return user pools json string
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
        friend std::ostream &operator<<(std::ostream &os, const ListUsersInGroupResponse &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_LIST_USERS_IN_GROUP_RESPONSE_H
