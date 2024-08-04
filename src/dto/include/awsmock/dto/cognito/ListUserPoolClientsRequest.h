//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_LIST_USERPOOL_CLIENTS_REQUEST_H
#define AWSMOCK_DTO_COGNITO_LIST_USERPOOL_CLIENTS_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief List user pool clients request
     *
     * @code(.json)
     * {
     *   "MaxResults": number,
     *   "NextToken": "string",
     *   "UserPoolId": "string"
     * }
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListUserPoolClientsRequest : public Dto::Common::BaseRequest {

        /**
         * User pool ID
         */
        std::string userPoolId{};

        /**
         * Max results
         */
        int maxResults;

        /**
         * Next token
         */
        std::string nextToken;

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
        friend std::ostream &operator<<(std::ostream &os, const ListUserPoolClientsRequest &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_LIST_USERPOOL_CLIENTS_REQUEST_H
