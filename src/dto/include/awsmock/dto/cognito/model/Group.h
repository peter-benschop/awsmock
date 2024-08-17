//
// Created by vogje01 on 5/31/24.
//

#ifndef AWSMOCK_DTO_COGNITO_GROUP_H
#define AWSMOCK_DTO_COGNITO_GROUP_H


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

    struct Group {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Group name
         */
        std::string groupName;

        /**
         * User pool Id
         */
        std::string userPoolId;

        /**
         * Description
         */
        std::string description;

        /**
         * Role ARN
         */
        std::string roleArn;

        /**
         * Precedence
         */
        int precedence;

        /**
         * Created
         */
        system_clock::time_point created = system_clock::now();

        /**
         * Last modified
         */
        system_clock::time_point modified = system_clock::now();

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
        friend std::ostream &operator<<(std::ostream &os, const Group &r);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_GROUP_H
