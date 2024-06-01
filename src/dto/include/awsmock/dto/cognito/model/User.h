//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_USER_H
#define AWSMOCK_DTO_COGNITO_USER_H

// C++ includes
#include <map>
#include <string>

// Poco includes
#include <Poco/JSON/Object.h>

// Boost includes
#include <boost/date_time/posix_time/posix_time.hpp>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/cognito/model/Group.h>
#include <awsmock/entity/cognito/UserAttribute.h>
#include <awsmock/entity/cognito/UserStatus.h>

namespace AwsMock::Dto::Cognito {

    using std::chrono::system_clock;

    /**
     * @brief Cognito user DTO
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct User {

        /**
         * MongoDB OID
         */
        std::string oid;

        /**
         * Aws region
         */
        std::string region;

        /**
         * User pool ID
         */
        std::string userPoolId;

        /**
         * User name
         */
        std::string userName;

        /**
         * Enabled
         */
        bool enabled;

        /**
         * Attributes
         */
        //UserAttributeList userAttributes;

        /**
         * Status
         */
        //UserStatus userStatus;

        /**
         * Password
         */
        std::string password;

        /**
         * Groups
         */
        std::vector<Group> groups;

        /**
         * Creation date
         */
        system_clock::time_point created = system_clock::now();

        /**
         * Last modification date
         */
        system_clock::time_point modified = system_clock::now();

        /**
         * @brief Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * @brief Converts the entity to a JSON string
         *
         * @return DTO as string.
         */
        std::string ToJson() const;

        /**
         * Converts the entity to a JSON object
         *
         * @param jsonObject JSON object.
         */
        void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

        /**
         * @brief Converts the entity to a string representation.
         *
         * @return entity as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @param os output stream
         * @param user user entity
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const User &user);
    };

    typedef std::vector<User> UserList;

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_USER_H
