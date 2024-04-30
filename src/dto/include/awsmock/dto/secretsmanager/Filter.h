//
// Created by vogje01 on 4/11/24.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_FILTER_H
#define AWSMOCK_DTO_SECRETSMANAGER_FILTER_H


// C++ standard includes
#include <sstream>
#include <string>
#include <vector>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMoc includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Secrets list filter
     *
     * Example:
     * @code{.json}
     * "Filters": [
     *   {
     *      "Key": "string",
     *      "Values": [ "string" ]
     *   }
     * ]
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Filter {

        /**
         * Filter key
         */
        std::string key;

        /**
         * Filter values array
         */
        std::vector<std::string> values;

        /**
         * Converts the DTO to a JSON object.
         *
         * @return DTO as JSON object.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Converts the JSON object to DTO.
         *
         * @param jsonObject JSON object
         */
        void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

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
        friend std::ostream &operator<<(std::ostream &os, const Filter &f);
    };

}// namespace AwsMock::Dto::SecretsManager

#endif//AWSMOCK_DTO_SECRETSMANAGER_FILTER_H
