//
// Created by vogje01 on 4/30/24.
//

#ifndef AWSMOCK_DTO_LAMBDA_TAGS_H
#define AWSMOCK_DTO_LAMBDA_TAGS_H

// C++ standard includes
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::Lambda {

    struct Tags {

        /**
         * Tags
         */
        std::map<std::string, std::string> tags;

        /**
         * Checks whether a tags with the given tags key exists.
         *
         * @param key key of the tags
         * @return true if tags with the given key exists.
         */
        bool HasTag(const std::string &key);

        /**
         * Returns a given tags value by key
         *
         * @param key key of the tags
         * @return tag value
         */
        std::string GetTagValue(const std::string &key);

        /**
         * Convert to a JSON array
         *
         * @return JSON array
         */
        [[nodiscard]] array ToDocument() const;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Convert to a JSON string
         *
         * @param document JSON object
         */
        void FromDocument(const view_or_value<view, value> &document);

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const Tags &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_TAGS_H
