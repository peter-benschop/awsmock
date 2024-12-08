//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_COGNITO_CLIENT_COMMAND_H
#define AWSMOCK_DTO_COMMON_COGNITO_CLIENT_COMMAND_H

// C++ includes
#include <sstream>
#include <string>

// Boost includes
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/dto/common/BaseClientCommand.h>
#include <awsmock/dto/common/UserAgent.h>

namespace AwsMock::Dto::Common {

    namespace http = boost::beast::http;

    enum class CognitoCommandType {
        CREATE_USER_POOL,
        CREATE_USER_POOL_CLIENT,
        CREATE_USER_POOL_DOMAIN,
        UPDATE_USER_POOL,
        UPDATE_USER_POOL_DOMAIN,
        UPDATE_USER_POOL_CLIENT,
        LIST_USER_POOL_CLIENTS,
        LIST_USER_POOL_COUNTERS,
        DESCRIBE_USER_POOL,
        DESCRIBE_USER_POOL_CLIENTS,
        DELETE_USER_POOL,
        DELETE_USER_POOL_CLIENT,
        LIST_USER_POOLS,
        LIST_USERS,
        LIST_USER_COUNTERS,
        CREATE_USER,
        ENABLE_USER,
        DISABLE_USER,
        DELETE_USER,
        CREATE_GROUP,
        LIST_GROUPS,
        DELETE_GROUP,
        ADD_USER_TO_GROUP,
        LIST_USERS_IN_GROUP,
        REMOVE_USER_FROM_GROUP,
        INITIATE_AUTH,
        RESPOND_TO_AUTH_CHALLENGE,
        SIGN_UP,
        GLOBAL_SIGN_OUT,
        ADMIN_CREATE_USER,
        ADMIN_GET_USER,
        ADMIN_ENABLE_USER,
        ADMIN_DISABLE_USER,
        ADMIN_DELETE_USER,
        ADMIN_ADD_USER_TO_GROUP,
        ADMIN_REMOVE_USER_FROM_GROUP,
        ADMIN_CONFIRM_SIGN_UP,
        UNKNOWN
    };

    static std::map<CognitoCommandType, std::string> CognitoCommandTypeNames{
            {CognitoCommandType::CREATE_USER_POOL, "CreateUserPool"},
            {CognitoCommandType::CREATE_USER_POOL_DOMAIN, "CreateUserPoolDomain"},
            {CognitoCommandType::UPDATE_USER_POOL, "UpdateUserPool"},
            {CognitoCommandType::UPDATE_USER_POOL_DOMAIN, "UpdateUserPoolDomain"},
            {CognitoCommandType::UPDATE_USER_POOL_DOMAIN, "UpdateUserPoolClient"},
            {CognitoCommandType::DESCRIBE_USER_POOL, "DescribeUserPool"},
            {CognitoCommandType::LIST_USER_POOLS, "ListUserPools"},
            {CognitoCommandType::LIST_USER_POOL_CLIENTS, "ListUserPoolClients"},
            {CognitoCommandType::LIST_USER_POOL_COUNTERS, "ListUserPoolCounters"},
            {CognitoCommandType::LIST_USERS, "ListUsers"},
            {CognitoCommandType::LIST_USER_COUNTERS, "ListUserCounters"},
            {CognitoCommandType::DESCRIBE_USER_POOL, "DescribeUserPool"},
            {CognitoCommandType::DESCRIBE_USER_POOL_CLIENTS, "DescribeUserPoolClients"},
            {CognitoCommandType::DELETE_USER_POOL, "DeleteUserPool"},
            {CognitoCommandType::DELETE_USER_POOL_CLIENT, "DeleteUserPoolClient"},
            {CognitoCommandType::CREATE_USER, "CreateUser"},
            {CognitoCommandType::ENABLE_USER, "EnableUser"},
            {CognitoCommandType::DISABLE_USER, "DisableUser"},
            {CognitoCommandType::DELETE_USER, "DeleteUser"},
            {CognitoCommandType::CREATE_GROUP, "CreateGroup"},
            {CognitoCommandType::LIST_GROUPS, "ListGroups"},
            {CognitoCommandType::DELETE_GROUP, "DeleteGroup"},
            {CognitoCommandType::ADD_USER_TO_GROUP, "AdminAddUserToGroup"},
            {CognitoCommandType::LIST_USERS_IN_GROUP, "ListUsersInGroup"},
            {CognitoCommandType::REMOVE_USER_FROM_GROUP, "AdminRemoveUserFromGroup"},
            {CognitoCommandType::CREATE_USER_POOL_CLIENT, "CreateUserPoolClient"},
            {CognitoCommandType::INITIATE_AUTH, "InitiateAuth"},
            {CognitoCommandType::RESPOND_TO_AUTH_CHALLENGE, "RespondToAuthChallenge"},
            {CognitoCommandType::SIGN_UP, "SignUp"},
            {CognitoCommandType::ADMIN_CREATE_USER, "AdminCreateUser"},
            {CognitoCommandType::ADMIN_GET_USER, "AdminGetUser"},
            {CognitoCommandType::ADMIN_ENABLE_USER, "AdminEnableUser"},
            {CognitoCommandType::ADMIN_DISABLE_USER, "AdminDisableUser"},
            {CognitoCommandType::ADMIN_DELETE_USER, "AdminDeleteUser"},
            {CognitoCommandType::ADMIN_CONFIRM_SIGN_UP, "AdminConfirmSignUp"},
            {CognitoCommandType::GLOBAL_SIGN_OUT, "GlobalSignOut"},
            {CognitoCommandType::ADMIN_ADD_USER_TO_GROUP, "AdminAddUserToGroup"},
            {CognitoCommandType::ADMIN_REMOVE_USER_FROM_GROUP, "AdminRemoveUserFromGroup"}};

    [[maybe_unused]] static std::string CognitoCommandTypeToString(const CognitoCommandType commandType) {
        return CognitoCommandTypeNames[commandType];
    }

    [[maybe_unused]] static CognitoCommandType CognitoCommandTypeFromString(const std::string &commandType) {
        for (auto &[fst, snd]: CognitoCommandTypeNames) {
            if (Core::StringUtils::StartsWith(commandType, snd)) {
                return fst;
            }
        }
        return CognitoCommandType::UNKNOWN;
    }

    /**
     * @brief Cognito client command
     *
     * The Cognito client command is used as a standardized way of interpreting the different ways the clients are calling the REST services. Each client type is using a
     * different way of calling the AWS REST services.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CognitoClientCommand : public BaseClientCommand {

        /**
         * Client command
         */
        CognitoCommandType command;

        /**
         * Bucket
         */
        std::string poolName;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Getś the value from the user-agent string
         *
         * @param request HTTP server request
         * @param region AWS region
         * @param user AWS user
         */
        void FromRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user);

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
        friend std::ostream &operator<<(std::ostream &os, const CognitoClientCommand &i);
    };

}// namespace AwsMock::Dto::Common

#endif// AWSMOCK_DTO_COMMON_COGNITO_CLIENT_COMMAND_H
