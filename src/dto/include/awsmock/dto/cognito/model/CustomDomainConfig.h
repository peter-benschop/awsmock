//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_DTO_COGNITO_CUSTOM_DOMAIN_CONFIG_H
#define AWSMOCK_DTO_COGNITO_CUSTOM_DOMAIN_CONFIG_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Custom domain config
     *
     * @code{.json}
     * "CustomDomainConfig": {
     *     "CertificateArn": "string"
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CustomDomainConfig {

        /**
         * CertificateArn
         */
        std::string certificateArn;

        /**
         * @brief Convert from a JSON object.
         *
         * @param document json object
         */
        void FromDocument(const view_or_value<view, value> &document) {

            try {

                certificateArn = Core::Bson::BsonUtils::GetStringValue(document, "CertificateArn");

            } catch (bsoncxx::exception &exc) {
                log_error << exc.what();
                throw Core::JsonException(exc.what());
            }
        }

        /**
         * @brief Convert to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const {
            try {

                document document;
                Core::Bson::BsonUtils::SetStringValue(document, "CertificateArn", certificateArn);
                return document.extract();

            } catch (bsoncxx::exception &exc) {
                log_error << exc.what();
                throw Core::JsonException(exc.what());
            }
        }
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_CUSTOM_DOMAIN_CONFIG_H
