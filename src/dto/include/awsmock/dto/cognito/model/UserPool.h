//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_COGNITO_MODEL_USER_POOL_H
#define AWSMOCK_DTO_COGNITO_MODEL_USER_POOL_H

// C++ includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::Cognito {

    using std::chrono::system_clock;

    struct UserPool {

        /**
         * ID
         */
        std::string id;

        /**
         * Region
         */
        std::string region;

        /**
         * Name
         */
        std::string name;

        /**
         * User pool ID
         */
        std::string userPoolId;

        /**
         * User pool ARN
         */
        std::string arn;

        /**
         * User pool domain
         */
        std::string domain;

        /**
         * Created
         */
        system_clock::time_point created;

        /**
         * Last modified
         */
        system_clock::time_point modified;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Convert to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
        friend std::ostream &operator<<(std::ostream &os, const UserPool &r);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_MODEL_USER_POOL_H
