//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_LIST_USER_RESPONSE_H
#define AWSMOCK_DTO_TRANSFER_LIST_USER_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/transfer/model/User.h>

namespace AwsMock::Dto::Transfer {

    /**
     * @brief List FTP user response
     *
     * Example
     * @code{.json}
     * {
     *   "NextToken": "eyJNYXJrZXIiOiBudWxsLCAiYm90b1X0cnVuU2F0ZV9hbW91bnQiOiAyfQ==",
     *   "ServerId": "s-01234567890abcdef",
     *   "Users": [
     *      {
     *         "Arn": "arn:aws:transfer:us-east-1:176354371281:user/s-01234567890abcdef/charlie",
     *         "HomeDirectory": "/tests/home/charlie",
     *         "SshPublicKeyCount": 1,
     *         "Role": "arn:aws:iam::176354371281:role/transfer-role1",
     *         "Tags": [
     *            {
     *               "Key": "Name",
     *               "Value": "user1"
     *            }
     *         ],
     *         "UserName": "my_user"
     *      }
     *   ]
     *   }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListUsersResponse {

        /**
         * Region
         */
        std::string region;

        /**
         * Next token ID
         */
        std::vector<User> users;

        /**
         * Server ID
         */
        std::string serverId;

        /**
         * Token
         */
        std::string nextToken;

        /**
         * @brief Creates a JSON string from the object.
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
        friend std::ostream &operator<<(std::ostream &os, const ListUsersResponse &r);
    };

}// namespace AwsMock::Dto::Transfer

#endif// AWSMOCK_DTO_TRANSFER_LIST_USER_RESPONSE_H
