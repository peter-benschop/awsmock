//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_TRANSFER_USER_H
#define AWSMOCK_DTO_TRANSFER_USER_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::Transfer {

    /**
     * @brief Transfer server user
     *
     * Example
     * @code{.json}
     * @endcode
     * {
     *   "Arn": "arn:aws:transfer:us-east-1:176354371281:user/s-01234567890abcdef/charlie",
     *   "HomeDirectory": "/data/home/charlie",
     *   "SshPublicKeyCount": 1,
     *   "Role": "arn:aws:iam::176354371281:role/transfer-role1",
     *   "Tags": [
     *      {
     *         "Key": "Name",
     *         "Value": "user1"
     *      }
     *   ],
     *   "UserName": "my_user"
     * }
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct User {

        /**
         * Region
         */
        std::string region;

        /**
         * User name
         */
        std::string userName;

        /**
         * ARN
         */
        std::string arn;

        /**
         * Role
         */
        std::string role;

        /**
         * Ssh public key count
         */
        int sshPublicKeyCount;

        /**
         * Home directory
         */
        std::string homeDirectory;

        /**
         * Password
         */
        std::string password;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts a JSON string to a user
         *
         * @param document JSON object
         */
        void FromDocument(const view_or_value<view, value> &document);

        /**
         * @brief Converts a JSON string to a list of users
         *
         * @param jsonString JSON string
         * @return list of users
         */
        static std::vector<User> FromJsonList(const std::string &jsonString);

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as JSON string
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
        friend std::ostream &operator<<(std::ostream &os, const User &r);
    };

    typedef std::vector<User> UserList;

}// namespace AwsMock::Dto::Transfer

#endif// AWSMOCK_DTO_TRANSFER_USER_H
