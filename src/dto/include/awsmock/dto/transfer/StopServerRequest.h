//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_STOP_SERVER_REQUEST_H
#define AWSMOCK_DTO_TRANSFER_STOP_SERVER_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/transfer/Server.h>

namespace AwsMock::Dto::Transfer {

    struct StopServerRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Maximal number of results
         */
        std::string serverId;

        /**
         * Parse a JSON stream
         *
         * @param body json input stream
         */
        void FromJson(const std::string &body);

        /**
         * Creates a JSON string from the object.
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
        friend std::ostream &operator<<(std::ostream &os, const StopServerRequest &r);
    };

}// namespace AwsMock::Dto::Transfer

#endif// AWSMOCK_DTO_TRANSFER_STOP_SERVER_REQUEST_H
