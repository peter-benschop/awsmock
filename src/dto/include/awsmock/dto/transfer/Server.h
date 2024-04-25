//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_TRANSFER_SERVER_H
#define AWSMOCK_DTO_TRANSFER_SERVER_H

// C++ includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>

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
     * Converts the DTO to a JSON representation.
     *
     * @return DTO as string for logging.
     */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
     * Converts the DTO to a JSON representation.
     *
     * @return DTO as JSON string
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
        friend std::ostream &operator<<(std::ostream &os, const Server &r);
    };

}// namespace AwsMock::Dto::Transfer

#endif//AWSMOCK_DTO_TRANSFER_SERVER_H
