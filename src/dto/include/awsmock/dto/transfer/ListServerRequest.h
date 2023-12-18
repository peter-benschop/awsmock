//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_LIST_SERVER_REQUEST_H
#define AWSMOCK_DTO_TRANSFER_LIST_SERVER_REQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::Transfer {

  struct ListServerRequest {

    /**
     * Region
     */
    std::string region;

    /**
     * Maximal number of results
     */
    int maxResults;

    /**
     * Token
     */
    std::string nextToken;

    /**
     * Creates a JSON string from the object.
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson() const;

    /**
     * Parse a JSON stream
     *
     * @param body json input stream
     */
    void FromJson(const std::string &body);

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
    friend std::ostream &operator<<(std::ostream &os, const ListServerRequest &r);

  };

} // namespace AwsMock::Dto::lambda

#endif // AWSMOCK_DTO_TRANSFER_LIST_SERVER_REQUEST_H
