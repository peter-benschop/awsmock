//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_COGNITO_CLIENT_COMMAND_H
#define AWSMOCK_DTO_COMMON_COGNITO_CLIENT_COMMAND_H

// C++ includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/RegularExpression.h>

// AwsMock includes
#include "awsmock/core/exception/JsonException.h"
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/dto/common/BaseClientCommand.h>
#include <awsmock/dto/common/HttpMethod.h>
#include <awsmock/dto/common/UserAgent.h>

namespace AwsMock::Dto::Common {

    enum class CognitoCommandType {
        CREATE_USER_POOL,
        CREATE_USER,
        DELETE_USER_POOL,
        UNKNOWN
    };

    static std::map<CognitoCommandType, std::string> CognitoCommandTypeNames{
            {CognitoCommandType::CREATE_USER_POOL, "CreateUserPool"},
            {CognitoCommandType::CREATE_USER, "CreateUser"},
            {CognitoCommandType::DELETE_USER_POOL, "DeleteUserPool"},
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
         * Gets command type from the user agent
         *
         * @param httpMethod HTTP request method
         * @param userAgent HTTP user agent
         */
        void GetCommandFromUserAgent(const HttpMethod &httpMethod, const UserAgent &userAgent);

        /**
         * Getś the value from the user-agent string
         *
         * @param method HTTP method
         * @param request HTTP server request
         * @param region AWS region
         * @param user AWS user
         */
        void FromRequest(const HttpMethod &method, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user);

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
