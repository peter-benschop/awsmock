//
// Created by vogje01 on 4/9/24.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_SECRET_TAGS_H
#define AWSMOCK_DTO_SECRETSMANAGER_SECRET_TAGS_H


// C++ standard includes
#include <map>
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMoc includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SecretsManager {

    /**
     * Secret tags
     *
     * Example:
     * @verbatim
     * "Tags": [
     *  {
     *    "Key": "string",
     *    "Value": "string"
     *  }
     * ]
     * @endverbatim
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct SecretTags {

        /**
         * Map of Tags
         */
        std::map<std::string, std::string> tags;

        /**
         * Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Array ToJsonArray() const;

        /**
         * Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Converts a JSON representation to s DTO.
         *
         * @param jsonObject JSON object.
         */
        void FromJson(const Poco::JSON::Object::Ptr &jsonObject);

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
        friend std::ostream &operator<<(std::ostream &os, const SecretTags &r);
    };

}// namespace AwsMock::Dto::SecretsManager
#endif// AWSMOCK_DTO_SECRETSMANAGER_SECRET_TAGS_H
