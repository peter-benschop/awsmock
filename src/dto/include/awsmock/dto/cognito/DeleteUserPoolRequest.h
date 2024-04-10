//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_DELETEUSERPOOLREQUEST_H
#define AWSMOCK_DTO_COGNITO_DELETEUSERPOOLREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMOck includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::Cognito {

  struct DeleteUserPoolRequest {

    /**
     * AWS region
     */
    std::string region;

    /**
     * User pool userPoolId
     */
    std::string userPoolId;

    /**
     * Convert from a JSON object.
     *
     * @param payload json string object
     */
    void FromJson(const std::string &payload);

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
    friend std::ostream &operator<<(std::ostream &os, const DeleteUserPoolRequest &i);

  };

} // namespace AwsMock::Dto::Cognito

#endif // AWSMOCK_DTO_COGNITO_DELETEUSERPOOLREQUEST_H
