//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_DB_ENTITY_COGNITO_USER_POOL_DOMAIN_H
#define AWSMOCK_DB_ENTITY_COGNITO_USER_POOL_DOMAIN_H

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Database::Entity::Cognito {

    using bsoncxx::to_json;
    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    /**
     * @brief Cognito user pool domain
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct UserPoolDomain {

        /**
         * Domain name
         */
        std::string domain;
    };

}// namespace AwsMock::Database::Entity::Cognito

#endif// AWSMOCK_DB_ENTITY_COGNITO_USER_POOL_DOMAIN_H
