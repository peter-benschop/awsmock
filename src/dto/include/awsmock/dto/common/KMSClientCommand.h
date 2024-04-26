//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_KMS_CLIENT_COMMAND_H
#define AWSMOCK_DTO_COMMON_KMS_CLIENT_COMMAND_H

// C++ includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/HttpMethod.h>
#include <awsmock/dto/common/UserAgent.h>

namespace AwsMock::Dto::Common {

    enum class KMSCommandType {
        CREATE_KEY,
        DELETE_KEY,
        UNKNOWN
    };

    static std::map<KMSCommandType, std::string> KMSCommandTypeNames{
            {KMSCommandType::CREATE_KEY, "create-key"},
            {KMSCommandType::DELETE_KEY, "delete-key"},
    };

    [[maybe_unused]] static std::string KMSCommandTypeToString(KMSCommandType commandType) {
        return KMSCommandTypeNames[commandType];
    }

    [[maybe_unused]] static KMSCommandType KMSCommandTypeFromString(const std::string &commandType) {
        for (auto &it: KMSCommandTypeNames) {
            if (Core::StringUtils::EqualsIgnoreCase(commandType, it.second)) {
                return it.first;
            }
        }
        return KMSCommandType::UNKNOWN;
    }

    /**
     * KMS client command
     * <p>
     * The KMS client command is used as a standardized way of interpreting the different ways the clients are calling the REST services. Each client type is using a different way of
     * calling the AWS REST services.
     * </p>
     *
     * @author jens.vogt@opitz-consulting.com
     */
    struct KMSClientCommand {

        /**
         * HTTP request type
         */
        HttpMethod method;

        /**
         * Client region
         */
        std::string region;

        /**
         * Client user
         */
        std::string user;

        /**
         * Client command
         */
        KMSCommandType command;

        /**
         * Content type
         */
        std::string contentType;

        /**
         * Message body
         */
        std::string payload;

        /**
         * Returns the message body as string.
         *
         * @param request HTTP request
         * @return message body as string
         */
        static std::string GetBodyAsString(Poco::Net::HTTPServerRequest &request);

        /**
         * Returns the command from HTTP header
         *
         * @param request HTTP request
         * @return command string
         */
        std::string GetCommandFromHeader(Poco::Net::HTTPServerRequest &request) const;

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
         * Convert to a JSON string
         *
         * @return JSON string
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
        friend std::ostream &operator<<(std::ostream &os, const KMSClientCommand &i);
    };

}// namespace AwsMock::Dto::Common

#endif// AWSMOCK_DTO_COMMON_KMS_CLIENT_COMMAND_H
