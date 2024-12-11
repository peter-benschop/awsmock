//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SNS_MESSAGE_ATTRIBUTE_H
#define AWSMOCK_DB_ENTITY_SNS_MESSAGE_ATTRIBUTE_H

// C++ includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Database::Entity::SNS {

    /**
     * SNS message attribute entity
     *
     * @author jens.vogt\@opitz-consulting.com
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
        [[maybe_unused]] [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * Converts the entity to a JSON object
         *
         * @return DTO as JSON object for logging.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument();

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

    typedef MessageAttribute MessageAttribute;
    typedef std::vector<MessageAttribute> MessageAttributeList;

}// namespace AwsMock::Database::Entity::SNS

#endif// AWSMOCK_DB_ENTITY_SNS_MESSAGE_ATTRIBUTE_H
