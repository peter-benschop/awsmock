//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_LIST_USERPOOL_RESPONSE_H
#define AWSMOCK_DTO_COGNITO_LIST_USERPOOL_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/cognito/UserPool.h>

namespace AwsMock::Dto::Cognito {

    /**
     * List user pool response
     *
     * @author jens.vogt@opitz-consulting.com
     */
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
        friend std::ostream &operator<<(std::ostream &os, const ListUserPoolResponse &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_LIST_USERPOOL_RESPONSE_H
