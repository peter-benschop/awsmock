//
// Created by vogje01 on 4/8/24.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_VERSION_IDS_TO_STAGES_H
#define AWSMOCK_DTO_SECRETSMANAGER_VERSION_IDS_TO_STAGES_H

// C++ standard includes
#include <map>
#include <string>

// AwsMoc includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Secrets manager version ID and stages
     *
     * Example:
     * @code{.json}
     * "EXAMPLE1-90ab-cdef-fedc-ba987SECRET1": [
     *   "AWSPREVIOUS"
     * ],
     * "EXAMPLE2-90ab-cdef-fedc-ba987SECRET2": [
     *   "AWSCURRENT"
     * ]
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct VersionIdsToStages {

        /**
         * Version/stages map
         */
        std::map<std::string, std::vector<std::string>> versions;

        /**
         * @brief Converts the DTO to a JSON representation.
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
        friend std::ostream &operator<<(std::ostream &os, const VersionIdsToStages &r);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif// AWSMOCK_DTO_SECRETSMANAGER_VERSION_IDS_TO_STAGES_H
