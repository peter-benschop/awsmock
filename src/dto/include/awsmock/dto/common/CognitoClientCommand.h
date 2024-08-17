//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_COGNITO_CLIENT_COMMAND_H
#define AWSMOCK_DTO_COMMON_COGNITO_CLIENT_COMMAND_H

// C++ includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/RegularExpression.h>

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
    namespace ip = boost::asio::ip;

    enum class CognitoCommandType {
        CREATE_USER_POOL,
        CREATE_USER_POOL_CLIENT,
        CREATE_USER_POOL_DOMAIN,
        DESCRIBE_USER_POOL,
        DELETE_USER_POOL,
        CREATE_USER,
        ENABLE_USER,
        DISABLE_USER,
        DELETE_USER,
        CREATE_GROUP,
        DELETE_GROUP,
        ADD_USER_TO_GROUP,
        LIST_USERS_IN_GROUP,
        REMOVE_USER_FROM_GROUP,
        UNKNOWN
    };

    static std::map<CognitoCommandType, std::string> CognitoCommandTypeNames{
            {CognitoCommandType::CREATE_USER_POOL, "CreateUserPool"},
            {CognitoCommandType::CREATE_USER_POOL_DOMAIN, "CreateUserPoolDomain"},
            {CognitoCommandType::DESCRIBE_USER_POOL, "DescribeUserPool"},
            {CognitoCommandType::DELETE_USER_POOL, "DeleteUserPool"},
            {CognitoCommandType::CREATE_USER, "CreateUser"},
            {CognitoCommandType::ENABLE_USER, "EnableUser"},
            {CognitoCommandType::DISABLE_USER, "DisableUser"},
            {CognitoCommandType::DELETE_USER, "DeleteUser"},
            {CognitoCommandType::CREATE_GROUP, "CreateGroup"},
            {CognitoCommandType::DELETE_GROUP, "DeleteGroup"},
            {CognitoCommandType::ADD_USER_TO_GROUP, "AdminAddUserToGroup"},
            {CognitoCommandType::LIST_USERS_IN_GROUP, "ListUsersInGroup"},
            {CognitoCommandType::REMOVE_USER_FROM_GROUP, "AdminRemoveUserGromGroup"},
            {CognitoCommandType::CREATE_USER_POOL_CLIENT, "CreateUserPoolClient"},
    };

    [[maybe_unused]] static std::string CognitoCommandTypeToString(CognitoCommandType commandType) {
        return CognitoCommandTypeNames[commandType];
    }

    [[maybe_unused]] static CognitoCommandType CognitoCommandTypeFromString(const std::string &commandType) {
        for (auto &it: CognitoCommandTypeNames) {
            if (Core::StringUtils::StartsWith(commandType, it.second)) {
                return it.first;
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
