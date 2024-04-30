//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_ADMIN_CREATE_USER_REQUEST_H
#define AWSMOCK_DTO_COGNITO_ADMIN_CREATE_USER_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/cognito/MessageAction.h>
#include <awsmock/dto/cognito/UserAttribute.h>

namespace AwsMock::Dto::Cognito {

    /**
     * Create user request
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct AdminCreateUserRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * ID of the user pool
         */
        std::string userPoolId;

        /**
         * Name of the user
         */
        std::string userName;

        /**
         * Message action
         */
        MessageAction messageAction = MessageAction::SUPPRESS;

        /**
         * Temporary password
         */
        std::string temporaryPassword;

        /**
         * User userAttributes list
         */
        UserAttributeList userAttributes;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Convert from a JSON object.
         *
         * @param payload json string object
         */
        void FromJson(const std::string &payload);

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @param r request
         * @param os output stream
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const AdminCreateUserRequest &r);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_ADMIN_CREATE_USER_REQUEST_H
