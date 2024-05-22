//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_GET_ITEM_REQUEST_H
#define AWSMOCK_DTO_DYNAMODB_GET_ITEM_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/common/BaseRequest.h>
#include <awsmock/dto/dynamodb/GetItemKey.h>
#include <awsmock/dto/dynamodb/model/AttributeValue.h>

namespace AwsMock::Dto::DynamoDb {

    /**
     * @brief DynamoDB get item request
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct GetItemRequest : public Dto::Common::BaseRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Table name
         */
        std::string tableName;

        /**
         * Keys
         */
        std::map<std::string, AttributeValue> keys;

        /**
         * Projection exception
         */
        std::string projectionExpression;

        /**
         * Consistent read
         */
        bool consistentRead;

        /**
         * Return consumed capacity
         */
        bool returnConsumedCapacity;

        /**
         * Original HTTP request body
         */
        std::string body;

        /**
         * Original HTTP request headers
         */
        std::map<std::string, std::string> headers;

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
        friend std::ostream &operator<<(std::ostream &os, const GetItemRequest &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_GET_ITEM_REQUEST_H
