//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_LIST_USER_COUNTERS_RESPONSE_H
#define AWSMOCK_DTO_COGNITO_LIST_USER_COUNTERS_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/common/BaseRequest.h>
#include <awsmock/entity/cognito/User.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief List users response
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListUserCountersResponse : public Dto::Common::BaseRequest {

        /**
         * User entities
         */
        Database::Entity::Cognito::UserList users;

        /**
         * User entities
         */
        long total;

        /**
         * @brief Convert to a JSON string.
         *
         * @return user pools json string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const ListUserCountersResponse &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_LIST_USER_COUNTERS_RESPONSE_H
