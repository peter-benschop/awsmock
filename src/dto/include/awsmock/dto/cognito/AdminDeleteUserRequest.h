//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_ADMIN_DELETE_USER_REQUEST_H
#define AWSMOCK_DTO_COGNITO_ADMIN_DELETE_USER_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/cognito/BaseRequest.h>
#include <awsmock/dto/cognito/MessageAction.h>
#include <awsmock/dto/cognito/UserAttribute.h>

namespace AwsMock::Dto::Cognito {

    /**
     * Delete user request
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct AdminDeleteUserRequest : public BaseRequest {

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
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const AdminDeleteUserRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_ADMIN_DELETE_USER_REQUEST_H
