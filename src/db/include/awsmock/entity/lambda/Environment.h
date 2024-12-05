//
// Created by vogje01 on 03/09/2023.
//

#ifndef AWSMOCK_ENTITY_LAMBDA_ENVIRONMENT_H
#define AWSMOCK_ENTITY_LAMBDA_ENVIRONMENT_H

// C++ includes
#include <map>
#include <sstream>
#include <string>

// Poco includes
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/string/to_string.hpp>


// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Database::Entity::Lambda {

    /**
     * @brief Lambda environment entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Environment {

        /**
         * Variables
         */
        std::map<std::string, std::string> variables;

        /**
         * @brief Converts the MongoDB document to an entity
         *
         * @param mResult database view.
         */
        void FromDocument(std::optional<bsoncxx::document::view> mResult);

        /**
         * @brief Converts the JSON object to and entity
         *
         * @param jsonObject JSON object
         */
        void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

        /**
         * @brief Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;
    };

}// namespace AwsMock::Database::Entity::Lambda

#endif// AWSMOCK_ENTITY_LAMBDA_ENVIRONMENT_H
