//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_DTO_COGNITO_CUSTOM_DOMAIN_CONFIG_H
#define AWSMOCK_DTO_COGNITO_CUSTOM_DOMAIN_CONFIG_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>

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
         * @param jsonObject json object
         */
        void FromJson(const Poco::JSON::Object::Ptr &jsonObject) {

            try {

                Core::JsonUtils::GetJsonValueString("CertificateArn", jsonObject, certificateArn);

            } catch (Poco::Exception &exc) {
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }

        /**
         * @brief Convert to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const {
            try {

                Poco::JSON::Object rootJson;
                rootJson.set("CertificateArn", certificateArn);

                return rootJson;

            } catch (Poco::Exception &exc) {
                log_error << exc.message();
                throw Core::JsonException(exc.message());
            }
        }
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_CUSTOM_DOMAIN_CONFIG_H
