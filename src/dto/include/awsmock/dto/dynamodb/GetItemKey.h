//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_GET_ITEM_KEY_H
#define AWSMOCK_DTO_DYNAMODB_GET_ITEM_KEY_H

// C++ standard includes
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// AwsMock includes
#include "awsmock/core/exception/JsonException.h"
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/dynamodb/ProvisionedThroughput.h>

namespace AwsMock::Dto::DynamoDb {

    /**
     * DynamoDB get item key
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct GetItemKey {

        /**
         * Region
         */
        std::string type;

        /**
         * Table name
         */
        std::string value;

        /**
         * Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Parse a JSON stream
         *
         * @param jsonBody JSON string
         */
        void FromJson(const std::string &jsonBody);

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
        friend std::ostream &operator<<(std::ostream &os, const GetItemKey &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_GET_ITEM_KEY_H
