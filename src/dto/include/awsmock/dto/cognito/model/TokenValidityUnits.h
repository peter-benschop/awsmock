//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_COGNITO_MODEL_TOKEN_VALIDITY_UNITS_H
#define AWSMOCK_DTO_COGNITO_MODEL_TOKEN_VALIDITY_UNITS_H

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

    enum ValidityUnits {
        seconds,
        minutes,
        hours,
        days
    };

    static std::map<ValidityUnits, std::string> ValidityUnitsNames{
            {ValidityUnits::seconds, "seconds"},
            {ValidityUnits::minutes, "minutes"},
            {ValidityUnits::hours, "hours"},
            {ValidityUnits::days, "days"}};

    [[maybe_unused]] static std::string ValidityUnitToString(ValidityUnits validityUnits) {
        return ValidityUnitsNames[validityUnits];
    }

    [[maybe_unused]] static ValidityUnits ValidityUnitFromString(const std::string &validityUnits) {
        for (auto &it: ValidityUnitsNames) {
            if (it.second == validityUnits) {
                return it.first;
            }
        }
        return ValidityUnits::days;
    }

    struct TokenValidityUnits {

        /**
         * Access token
         */
        ValidityUnits accessToken = ValidityUnits::hours;

        /**
         * ID token
         */
        ValidityUnits idToken = ValidityUnits::hours;

        /**
         * Refresh token
         */
        ValidityUnits refreshToken = ValidityUnits::hours;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert from a JSON object
         *
         * @param JSON object
         */
        void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

        /**
         * @brief Convert to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
        friend std::ostream &operator<<(std::ostream &os, const TokenValidityUnits &r);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_MODEL_TOKEN_VALIDITY_UNITS_H
