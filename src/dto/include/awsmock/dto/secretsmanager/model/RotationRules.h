//
// Created by vogje01 on 4/8/24.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_ROTATION_RULES_H
#define AWSMOCK_DTO_SECRETSMANAGER_ROTATION_RULES_H

// C++ standard includes
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Rotation rules
     *
     * Example:
     * @code{.json}
     * {
     *   "AutomaticallyAfterDays": number,
     *   "Duration": "string",
     *   "ScheduleExpression": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct RotationRules {

        /**
         * Automatic rotation period
         */
        long automaticallyAfterDays;

        /**
         * Duration
         */
        std::string duration;

        /**
         * Duration
         */
        std::string scheduleExpression;

        /**
         * @brief Converts the DTO to a JSON object.
         *
         * @return DTO as string
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts a JSON representation to s DTO.
         *
         * @param jsonObject JSON object.
         */
        void FromDocument(const view_or_value<view, value> &jsonObject);

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const RotationRules &r);
    };

}//namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETSMANAGER_ROTATION_RULES_H
