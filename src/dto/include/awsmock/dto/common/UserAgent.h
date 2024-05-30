//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_USER_AGENT_H
#define AWSMOCK_DTO_COMMON_USER_AGENT_H

// C++ includes
#include <sstream>
#include <string>

// Boost includes
#include <boost/beast/http/message.hpp>

// AwsMock includes
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/common/UserAgent.h>

namespace AwsMock::Dto::Common {

    namespace http = boost::beast::http;
    namespace ip = boost::asio::ip;

    enum class UserAgentType {
        AWS_SDK_JAVA1,
        AWS_SDK_JAVA2,
        AWS_SDK_CPP,
        AWS_CLI,
        AWS_SDK_UNKNOWN
    };

    static std::map<UserAgentType, std::string> UserAgentTypeNames{
            {UserAgentType::AWS_SDK_JAVA1, "aws-sdk-java/1"},
            {UserAgentType::AWS_SDK_JAVA2, "aws-sdk-java/2"},
            {UserAgentType::AWS_SDK_CPP, "aws-sdk-cpp/2"},
            {UserAgentType::AWS_CLI, "aws-cli/2"},
            {UserAgentType::AWS_SDK_UNKNOWN, ""},
    };

    [[maybe_unused]] static std::string UserAgentTypeToString(UserAgentType userAgentType) {
        return UserAgentTypeNames[userAgentType];
    }

    [[maybe_unused]] static UserAgentType UserAgentTypeFromString(const std::string &userAgentType) {
        for (auto &it: UserAgentTypeNames) {
            if (Core::StringUtils::StartsWith(userAgentType, it.second)) {
                return it.first;
            }
        }
        return UserAgentType::AWS_SDK_UNKNOWN;
    }

    /**
     * @brief HTTP user agent
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct UserAgent {

        /**
         * Client application
         */
        std::string clientApplication;

        /**
         * Client language
         */
        std::string clientLanguage;

        /**
         * Client OS
         */
        std::string clientOs;

        /**
         * Client executable type
         */
        std::string clientExecutableType;

        /**
         * Client prompt
         */
        bool clientPrompt;

        /**
         * Client request module
         */
        std::string clientModule;

        /**
         * Client command
         */
        std::string clientCommand;

        /**
         * Client content type, default: application/xml
         */
        std::string contentType = "application/xml";

        /**
         * User agent type
         */
        UserAgentType type;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Gets the value from the user-agent string
         *
         * @param request HTTP server request
         */
        void FromRequest(Poco::Net::HTTPServerRequest &request);

        /**
         * Gets the value from the user-agent string
         *
         * @param request HTTP server request
         */
        void FromRequest(const http::request<http::dynamic_body> &request);

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
        friend std::ostream &operator<<(std::ostream &os, const UserAgent &i);
    };

}// namespace AwsMock::Dto::Common

#endif// AWSMOCK_DTO_COMMON_USER_AGENT_H
