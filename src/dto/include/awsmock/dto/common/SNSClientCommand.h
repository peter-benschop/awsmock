//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_SNS_CLIENT_COMMAND_H
#define AWSMOCK_DTO_COMMON_SNS_CLIENT_COMMAND_H

// C++ includes
#include <sstream>
#include <string>

// Boost includes
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/lexical_cast.hpp>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/common/BaseClientCommand.h>
#include <awsmock/dto/common/UserAgent.h>

namespace AwsMock::Dto::Common {

    namespace http = boost::beast::http;
    namespace ip = boost::asio::ip;

    enum class SNSCommandType {
        CREATE_TOPIC,
        LIST_TOPICS,
        GET_TOPIC_ATTRIBUTES,
        PUBLISH,
        SUBSCRIBE,
        UNSUBSCRIBE,
        LIST_SUBSCRIPTIONS_BY_TOPIC,
        TAG_RESOURCE,
        DELETE_TOPIC,
        UNKNOWN
    };

    static std::map<SNSCommandType, std::string> SNSCommandTypeNames{
            {SNSCommandType::CREATE_TOPIC, "create-topic"},
            {SNSCommandType::LIST_TOPICS, "list-topics"},
            {SNSCommandType::GET_TOPIC_ATTRIBUTES, "get-topic-attributes"},
            {SNSCommandType::PUBLISH, "publish"},
            {SNSCommandType::SUBSCRIBE, "subscribe"},
            {SNSCommandType::UNSUBSCRIBE, "unsubscribe"},
            {SNSCommandType::LIST_SUBSCRIPTIONS_BY_TOPIC, "list-subscriptions-by-topic"},
            {SNSCommandType::TAG_RESOURCE, "tag-resource"},
            {SNSCommandType::DELETE_TOPIC, "delete-topic"},
    };

    [[maybe_unused]] static std::string SNSCommandTypeToString(SNSCommandType commandType) {
        return SNSCommandTypeNames[commandType];
    }

    [[maybe_unused]] static SNSCommandType SNSCommandTypeFromString(const std::string &commandType) {
        for (auto &it: SNSCommandTypeNames) {
            if (Core::StringUtils::EqualsIgnoreCase(commandType, it.second)) {
                return it.first;
            }
        }
        return SNSCommandType::UNKNOWN;
    }

    /**
     * @brief The SNS client command is used as a standardized way of interpreting the different ways the clients are calling the REST services. Each client type is using a different way of calling the AWS REST services.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct SNSClientCommand : public BaseClientCommand {

        /**
         * @brief Client command
         */
        SNSCommandType command{};

        /**
         * @brief Returns the command from HTTP header
         *
         * @param request HTTP request
         * @return command string
         */
        std::string GetCommandFromHeader(const http::request<http::dynamic_body> &request) const;

        /**
         * @brief Getś the value from the user-agent string
         *
         * @param request HTTP server request
         * @param region AWS region
         * @param user AWS user
         */
        void FromRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user);

        /**
         * @brief Convert to a JSON string
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
        friend std::ostream &operator<<(std::ostream &os, const SNSClientCommand &i);
    };

}// namespace AwsMock::Dto::Common

#endif// AWSMOCK_DTO_COMMON_SNS_CLIENT_COMMAND_H
