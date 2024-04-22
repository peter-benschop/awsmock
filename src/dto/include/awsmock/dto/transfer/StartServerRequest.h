//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_START_SERVER_REQUEST_H
#define AWSMOCK_DTO_TRANSFER_START_SERVER_REQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/JsonException.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/transfer/Server.h>

namespace AwsMock::Dto::Transfer {

  struct StartServerRequest {

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
    friend std::ostream &operator<<(std::ostream &os, const StartServerRequest &r);

  };

} // namespace AwsMock::Dto::lambda

#endif // AWSMOCK_DTO_TRANSFER_START_SERVER_REQUEST_H
