//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_TRANSFER_SERVER_H
#define AWSMOCK_DTO_TRANSFER_SERVER_H

// C++ includes
#include <sstream>
#include <string>

// AwsMock includes
#include "awsmock/core/JsonUtils.h"
#include "awsmock/core/LogStream.h"
#include "awsmock/core/exception/JsonException.h"

namespace AwsMock::Dto::Transfer {

    struct Server {

        /**
         * ARN
         */
        std::string arn;

        /**
         * Domain
         */
        std::string domain;

        /**
         * Identity provider type
         */
        std::string identityProviderType;

        /**
         * Endpoint type
         */
        std::string endpointType;

        /**
         * Logging role
         */
        std::string loggingRole;

        /**
         * Server ID
         */
        std::string serverId;

        /**
         * State
         */
        std::string state;

        /**
         * User count
         */
        int userCount;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @param body DTO as JSON string
         */
        void FromJson(const std::string &body);

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as JSON string
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
        friend std::ostream &operator<<(std::ostream &os, const Server &r);
    };

}// namespace AwsMock::Dto::Transfer

#endif//AWSMOCK_DTO_TRANSFER_SERVER_H
