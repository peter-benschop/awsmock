//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_DOMAIN_RESPONSE_H
#define AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_DOMAIN_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Create user pool domain response
     *
     * Example:
     * @code{.json}
     * {
     *   "CloudFrontDomain": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CreateUserPoolDomainResponse : Common::BaseRequest {

        /**
         * Name of the user pool
         */
        std::string cloudFrontDomain;

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
        friend std::ostream &operator<<(std::ostream &os, const CreateUserPoolDomainResponse &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_DOMAIN_RESPONSE_H
