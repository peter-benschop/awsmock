//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_LIST_TABLE_REQUEST_H
#define AWSMOCK_DTO_DYNAMODB_LIST_TABLE_REQUEST_H

// C++ standard includes
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::DynamoDb {

    /**
     * @brief DynamoDB list table request
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListTableRequest : Common::BaseRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * The first table name that this operation will evaluate. Use the value that was returned for LastEvaluatedTableName
         * in a previous operation, so that you can obtain the next page of results.
         */
        std::string exclusiveStartTableName;

        /**
         * Limit, default is 100
         */
        int limit = 100;

        /**
         * Original HTTP request body
         */
        std::string body;

        /**
         * Original HTTP request headers
         */
        std::map<std::string, std::string> headers;

        /**
         * @brief Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Prepares the request to be sent to the DynamoDB container
         */
        void PrepareRequest();

        /**
         * @brief Parse a JSON stream
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const ListTableRequest &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_LIST_TABLE_REQUEST_H
