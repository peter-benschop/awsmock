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
#include <mongocxx/stdx.hpp>

namespace AwsMock::Database::Entity::Lambda {

    /**
     * @param Lambda environment entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Environment {

        /**
         * Variables
         */
        std::map<std::string, std::string> variables;

        /**
         * C@param onverts the MongoDB document to an entity
         *
         * @param mResult database view.
         */
        void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

        /**
         * @param Converts the entity to a JSON object
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;
    };

}// namespace AwsMock::Database::Entity::Lambda

#endif// AWSMOCK_ENTITY_LAMBDA_ENVIRONMENT_H
