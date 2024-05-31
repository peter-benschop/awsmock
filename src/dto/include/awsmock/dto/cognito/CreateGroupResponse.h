//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_CREATE_GROUP_RESPONSE_H
#define AWSMOCK_DTO_COGNITO_CREATE_GROUP_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/cognito/model/Group.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Create group response
     *
     * Example:
     * @code{.json}
     * {
     *   "Group": {
     *      "CreationDate": number,
     *      "Description": "string",
     *      "GroupName": "string",
     *      "LastModifiedDate": number,
     *      "Precedence": number,
     *      "RoleArn": "string",
     *      "UserPoolId": "string"
     *   }
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CreateGroupResponse : public Dto::Common::BaseRequest {

        /**
         * Group
         */
        Group group;

        /**
         * Convert to a JSON string.
         *
         * @return json string
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
        friend std::ostream &operator<<(std::ostream &os, const CreateGroupResponse &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_CREATE_GROUP_RESPONSE_H
