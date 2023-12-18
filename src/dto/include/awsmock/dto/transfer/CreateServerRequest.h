//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_CREATE_TRANSFER_REQUEST_H
#define AWSMOCK_DTO_TRANSFER_CREATE_TRANSFER_REQUEST_H

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
#include <awsmock/dto/transfer/Tag.h>
#include <awsmock/dto/transfer/IdentityProviderDetails.h>

namespace AwsMock::Dto::Transfer {

  struct CreateServerRequest {

    /**
     * Region
     */
    std::string region;

    /**
     * Domain
     */
    std::string domain;

    /**
     * Protocols
     */
    std::vector<std::string> protocols;

    /**
     * Tags
     */
    TagList tags;

    /**
     * Identity provider details
     */
    IdentityProviderDetails identityProviderDetails;

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
    friend std::ostream &operator<<(std::ostream &os, const CreateServerRequest &r);

  };

} // namespace AwsMock::Dto::lambda

#endif // AWSMOCK_DTO_TRANSFER_CREATE_TRANSFER_REQUEST_H
