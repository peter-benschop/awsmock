//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_DESCRIBE_USERPOOL_CLIENT_REQUEST_H
#define AWSMOCK_DTO_COGNITO_DESCRIBE_USERPOOL_CLIENT_REQUEST_H

// C++ standard includes

#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Describe user pool client request.
     *
     * Request to describe a user pool client.
     *
     * Example:
     * @code{.json}
     * {
     *   "UserPoolId": "string"
     *   "ClientId": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct DescribeUserPoolClientRequest : Common::BaseRequest {

        /**
         * User pool ID
         */
        std::string userPoolId;

        /**
         * User pool ID
         */
        std::string clientId;

        /**
         * @brief Convert from a JSON object.
         *
         * @param jsonString json string object
         */
        void FromJson(const std::string &jsonString);

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
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
        friend std::ostream &operator<<(std::ostream &os, const DescribeUserPoolClientRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_DESCRIBE_USERPOOL_CLIENT_REQUEST_H
