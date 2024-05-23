//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_ACCOUNT_SETTINGS_RESPONSE_H
#define AWSMOCK_DTO_LAMBDA_ACCOUNT_SETTINGS_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/common/BaseRequest.h>
#include <awsmock/dto/lambda/model/AccountLimit.h>
#include <awsmock/dto/lambda/model/AccountUsage.h>

namespace AwsMock::Dto::Lambda {

    /**
     * @brief Create function response
     *
     * Example:
     * @code{.json}
     * {
     *   "AccountLimit": {
     *     "CodeSizeUnzipped": number,
     *     "CodeSizeZipped": number,
     *     "ConcurrentExecutions": number,
     *     "TotalCodeSize": number,
     *     "UnreservedConcurrentExecutions": number
     *   },
     *   "AccountUsage": {
     *     "FunctionCount": number,
     *     "TotalCodeSize": number
     *   }
     * }
     * @endcode
     */
    struct AccountSettingsResponse : public Dto::Common::BaseRequest {

        /**
         * Account limits
         */
        AccountLimit accountLimit;

        /**
         * Account usage
         */
        AccountUsage accountUsage;

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
        friend std::ostream &operator<<(std::ostream &os, const AccountSettingsResponse &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_ACCOUNT_SETTINGS_RESPONSE_H
