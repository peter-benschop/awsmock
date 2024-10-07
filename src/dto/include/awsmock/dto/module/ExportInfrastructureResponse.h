//
// Created by vogje01 on 10/6/24.
//

#ifndef AWSMOCK_DTO_EXPORT_INFRASTRUCTURE_RESPONSE_H
#define AWSMOCK_DTO_EXPORT_INFRASTRUCTURE_RESPONSE_H

// C++ includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/module/model/Infrastructure.h>

namespace AwsMock::Dto::Module {

    /**
     * @brief Export infrastructure request
     *
     * Example:
     * @code{.json}
     * {
     *   "modules": ["string", ...],
     *   "onlyObjects": bool,
     *   "prettyPrint": bool,
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ExportInfrastructureResponse {

        /**
         * Modules
         */
        Infrastructure infrastructure;

        /**
         * Include objects
         */
        bool includeObjects;

        /**
         * Pretty print
         */
        bool prettyPrint;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        Poco::JSON::Object ToJsonObject();

        /**
         * Convert from a JSON object.
         *
         * @param payload json string object
         */
        std::string ToJson();

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString();

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, ExportInfrastructureResponse &r);
    };

}// namespace AwsMock::Dto::Module

#endif// AWSMOCK_DTO_EXPORT_INFRASTRUCTURE_RESPONSE_H
