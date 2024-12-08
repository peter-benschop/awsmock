//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_ADMIN_GET_USER_RESPONSE_H
#define AWSMOCK_DTO_COGNITO_ADMIN_GET_USER_RESPONSE_H

// C++ standard includes
#include <chrono>
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/cognito/model/MessageAction.h>
#include <awsmock/dto/cognito/model/UserAttribute.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    using std::chrono::system_clock;

    /**
     * @brief Get admin user response
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct AdminGetUserResponse : public Dto::Common::BaseRequest {

        /**
         * Name of the user
         */
        std::string userName;

        /**
         * Enabled flag
         */
        bool enabled = false;

        /**
         * User userAttributes list
         */
        UserAttributeList userAttributes;

        /**
         * Created
         */
        system_clock::time_point created = system_clock::now();

        /**
         * Modified
         */
        system_clock::time_point modfified = system_clock::now();

        /**
         * Convert from a JSON object.
         *
         * @param payload json string object
         */
        void FromJson(const std::string &payload);

        /**
         * Convert from a JSON object.
         *
         * @return JSON representation of the object
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
        friend std::ostream &operator<<(std::ostream &os, const AdminGetUserResponse &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_ADMIN_GET_USER_RESPONSE_H
