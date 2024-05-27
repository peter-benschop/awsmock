//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_DOMAIN_REQUEST_H
#define AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_DOMAIN_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/cognito/model/CustomDomainConfig.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Create user pool domain request
     *
     * Request to create a new user pool domain.
     *
     * Example:
     * @code{.json}
     * {
     *   "CustomDomainConfig": {
     *     "CertificateArn": "string"
     *   },
     *   "Domain": "string",
     *   "UserPoolId": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CreateUserPoolDomainRequest : public Dto::Common::BaseRequest {

        /**
         * Name of the user pool domain
         */
        std::string domain;

        /**
         * User pool of the domain
         */
        std::string userPoolId;

        /**
         * Custom domain config
         */
        CustomDomainConfig customDomainConfig;

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
        friend std::ostream &operator<<(std::ostream &os, const CreateUserPoolDomainRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_CREATE_USERPOOL_DOMAIN_REQUEST_H
