//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SSM_PARAMETER_TOPIC_H
#define AWSMOCK_DB_ENTITY_SSM_PARAMETER_TOPIC_H

// C++ includes
#include <chrono>
#include <string>
#include <vector>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database::Entity::SSM {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;
    using std::chrono::system_clock;

    /**
     * ssm parameter entity
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Parameter {

        /**
         * ID
         */
        std::string oid;

        /**
         * AWS region
         */
        std::string region;

        /**
         * Parameter name
         */
        std::string parameterName;

        /**
         * Value
         */
        std::string parameterValue;

        /**
         * Description
         */
        std::string description;

        /**
         * Parameter type
         */
        std::string type;

        /**
         * Tier
         */
        std::string tier;

        /**
         * Version
         */
        int version;

        /**
         * AWS ARN
         */
        std::string arn;

        /**
         * Topic tags
         */
        std::map<std::string, std::string> tags;

        /**
         * Creation date
         */
        system_clock::time_point created = system_clock::now();

        /**
         * Last modification date
         */
        system_clock::time_point modified = system_clock::now();

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * Converts the MongoDB document to an entity
         *
         * @param mResult MongoDB document view.
         */
        void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

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
        friend std::ostream &operator<<(std::ostream &os, const Parameter &q);
    };

    typedef std::vector<Parameter> ParameterList;

}// namespace AwsMock::Database::Entity::SSM

#endif// AWSMOCK_DB_ENTITY_SSM_PARAMETER_TOPIC_H
