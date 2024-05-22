//
// Created by vogje01 on 5/22/24.
//

#ifndef AWSMOCK_DTO_DYNAMODB_KEY_H
#define AWSMOCK_DTO_DYNAMODB_KEY_H

// C++ includes
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/dynamodb/model/AttributeValue.h>

namespace AwsMock::Dto::DynamoDb {

    /**
     * @brief DynamoDB item key
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Key {

        /**
         * Name
         */
        std::map<std::string, AttributeValue> keys;

        /**
         * Convert to JSON value
         *
         * @return JSON object
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Convert to JSON value
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Convert from JSON object.
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
        friend std::ostream &operator<<(std::ostream &os, const Key &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif//AWSMOCK_DTO_DYNAMODB_KEY_H
