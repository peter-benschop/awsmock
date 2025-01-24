//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_COGNITO_VALIDATION_DATA_H
#define AWSMOCK_DTO_COGNITO_VALIDATION_DATA_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/cognito/User.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief User attribute
     *
     * @par
     * Temporary user attributes that contribute to the outcomes of your pre sign-up Lambda trigger. This set of key-value pairs are for custom validation of information that you collect from your
     * users but don't need to retain. Your Lambda function can analyze this additional data and act on it. Your function might perform external API operations like logging user attributes and
     * validation data to Amazon CloudWatch Logs. Validation data might also affect the response that your function returns to Amazon Cognito, like automatically confirming the user if they sign
     * up from within your network.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ValidationData {

        /**
         * User attribute name
         */
        std::string name;

        /**
         * MessageAttribute value
         */
        std::string attributeValue;

        /**
         * @brief Converts the JSON string to a DTO
         *
         * @param document JSON object
         */
        void FromDocument(const view_or_value<view, value> &document);

        /**
         * @brief Convert to a JSON string.
         *
         * @return user pools json string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert to a JSON string.
         *
         * @return user pools json string
         */
        view_or_value<view, value> ToDocument() const;

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
        friend std::ostream &operator<<(std::ostream &os, const ValidationData &r);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_VALIDATION_DATA_H
