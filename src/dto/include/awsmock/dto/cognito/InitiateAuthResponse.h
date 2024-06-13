//
// Created by vogje01 on 11/25/23.
//

#ifndef AWSMOCK_DTO_COGNITO_INITIATE_AUTH_RESPONSE_H
#define AWSMOCK_DTO_COGNITO_INITIATE_AUTH_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/cognito/model/AuthenticationResult.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Initiate authentication request
     *
     * Example:
     * @code{.json}
     * {
     *   "AuthenticationResult": {
     *      "AccessToken": "string",
     *      "ExpiresIn": number,
     *      "IdToken": "string",
     *      "NewDeviceMetadata": {
     *         "DeviceGroupKey": "string",
     *         "DeviceKey": "string"
     *      },
     *      "RefreshToken": "string",
     *      "TokenType": "string"
     *   },
     *   "ChallengeName": "string",
     *   "ChallengeParameters": {
     *      "string" : "string"
     *   },
     *   "Session": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct InitiateAuthResponse : public Dto::Common::BaseRequest {

        /**
         * Authentication result
         */
        AuthenticationResult authenticationResult;

        /**
         * Session
         */
        std::string session;

        /**
         * Challenge name
         */
        std::string challengeName;

        /**
         * Challenge parameters
         */
        std::map<std::string, std::string> challengeParameters;

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
        friend std::ostream &operator<<(std::ostream &os, const InitiateAuthResponse &i);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_INITIATE_AUTH_RESPONSE_H
