//
// Created by vogje01 on 03/09/2023.
//

#ifndef AWSMOCK_ENTITY_LAMBDA_ENVIRONMENT_H
#define AWSMOCK_ENTITY_LAMBDA_ENVIRONMENT_H

// C++ includes
#include <map>
#include <string>

// Poco includes
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/string/to_string.hpp>


// AwsMock includes
#include <awsmock/core/BsonUtils.h>
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
        void FromDocument(const std::optional<view> &mResult);

        /**
         * @brief Converts the JSON object to and entity
         *
         * @param jsonObject JSON object
         */
        //void FromDocument(const view_or_value<view, value> &jsonObject);

        /**
         * @brief Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;
    };

}// namespace AwsMock::Database::Entity::Lambda

#endif// AWSMOCK_ENTITY_LAMBDA_ENVIRONMENT_H
