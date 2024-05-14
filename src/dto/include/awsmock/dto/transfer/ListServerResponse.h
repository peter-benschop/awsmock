//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_LIST_SERVER_RESPONSE_H
#define AWSMOCK_DTO_TRANSFER_LIST_SERVER_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>
#include <vector>

// AwsMock includes
#include "awsmock/core/exception/JsonException.h"
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/transfer/Server.h>

namespace AwsMock::Dto::Transfer {

    struct ListServerResponse {

        /**
         * Region
         */
        std::string region;

        /**
         * Next token ID
         */
        std::string nextToken;

        /**
         * Server list
         */
        std::vector<Server> servers;

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
        friend std::ostream &operator<<(std::ostream &os, const ListServerResponse &r);
    };

}// namespace AwsMock::Dto::Transfer

#endif// AWSMOCK_DTO_TRANSFER_LIST_SERVER_RESPONSE_H
