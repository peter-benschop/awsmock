//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_LISTUSERPOOLRESPONSE_H
#define AWSMOCK_DTO_COGNITO_LISTUSERPOOLRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/entity/cognito/UserPool.h>

namespace AwsMock::Dto::Cognito {

  struct ListUserPoolResponse {

    /**
     * User pool entities
     */
    Database::Entity::Cognito::UserPoolList userPools;

    /**
     * Convert to a JSON string.
     *
     * @return user pools json string
     */
    std::string ToJson();

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
    friend std::ostream &operator<<(std::ostream &os, const ListUserPoolResponse &i);

  };

} // namespace AwsMock::Dto::Cognito

#endif //AWSMOCK_DTO_COGNITO_LISTUSERPOOLRESPONSE_H
