//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_ADMIN_CREATE_USER_REQUEST_H
#define AWSMOCK_DTO_COGNITO_ADMIN_CREATE_USER_REQUEST_H

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
#include <awsmock/dto/cognito/MessageAction.h>
#include <awsmock/dto/cognito/UserAttribute.h>

namespace AwsMock::Dto::Cognito {

  struct AdminCreateUserRequest {

    /**
     * AWS region
     */
    std::string region;

    /**
     * ID of the user pool
     */
    std::string userPoolId;

    /**
     * Name of the user
     */
    std::string userName;

    /**
     * Message action
     */
    MessageAction messageAction = MessageAction::SUPPRESS;

    /**
     * Temporary password
     */
    std::string temporaryPassword;

    /**
     * User userAttributes list
     */
    UserAttributeList userAttributes;

    /**
     * Convert from a JSON object.
     *
     * @param payload json string object
     */
    void FromJson(const std::string &payload);

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
    friend std::ostream &operator<<(std::ostream &os, const AdminCreateUserRequest &i);

  };

} // namespace AwsMock::Dto::Cognito

#endif // AWSMOCK_DTO_COGNITO_ADMIN_CREATE_USER_REQUEST_H
