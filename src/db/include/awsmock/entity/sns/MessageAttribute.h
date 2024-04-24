//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SNS_MESSAGEATTRIBUTE_H
#define AWSMOCK_DB_ENTITY_SNS_MESSAGEATTRIBUTE_H

// C++ includes
#include <string>
#include <sstream>
#include <vector>
#include <map>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/Object.h>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

namespace AwsMock::Database::Entity::SNS {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::view_or_value;
    using bsoncxx::document::view;
    using bsoncxx::document::value;

    /**
     * SNS message attribute entity
     *
     * @author jens.vogt@opitz-consulting.com
     */
    struct MessageAttribute {

        /**
         * MessageAttribute name
         */
        std::string attributeName;

        /**
         * MessageAttribute value
         */
        std::string attributeValue;

        /**
         * Converts the entity to a MongoDB document
         *
         * @return entity as MongoDB document.
         */
        [[maybe_unused]] [[nodiscard]] view_or_value <view, value> ToDocument() const;

        /**
         * Converts the entity to a JSON object
         *
         * @return DTO as JSON object for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @param os output stream
         * @param m message attribute entity
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const MessageAttribute &m);

    };

    typedef struct MessageAttribute MessageAttribute;
    typedef std::vector <MessageAttribute> MessageAttributeList;

} // namespace AwsMock::Database::Entity::SNS

#endif // AWSMOCK_DB_ENTITY_SNS_MESSAGEATTRIBUTE_H
