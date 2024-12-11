//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_CREATE_TABLE_RESPONSE_H
#define AWSMOCK_DTO_DYNAMODB_CREATE_TABLE_RESPONSE_H

// C++ standard includes
#include <map>
#include <string>

// Boost include<
#include <boost/beast.hpp>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/dto/common/BaseRequest.h>
#include <awsmock/dto/dynamodb/model/TableStatus.h>

namespace AwsMock::Dto::DynamoDb {

    namespace http = boost::beast::http;

    /**
     * @brief Create table response DTO
     *
     * Example:
     * @code{.json}
     * {
     *   "TableDescription":
     *     {
     *       "AttributeDefinitions": [
     *           {
     *             "attributeName":"orgaNr",
     *             "AttributeType":"N"
     *           }
     *       ],
     *       "TableName":"test-table",
     *       "KeySchema":[
     *         {
     *           "attributeName":"orgaNr",
     *           "KeyType":"HASH"
     *         }
     *       ],
     *       "TableStatus":"ACTIVE",
     *       "CreationDateTime":1703158038.811,
     *       "ProvisionedThroughput":
     *         {
     *           "LastIncreaseDateTime":0.000,
     *           "LastDecreaseDateTime":0.000,
     *           "NumberOfDecreasesToday":0,
     *           "ReadCapacityUnits":1,
     *           "WriteCapacityUnits":1
     *         },
     *       "TableSizeBytes":0,
     *       "ItemCount":0,
     *       "TableArn":"arn:aws:dynamodb:ddblocal:000000000000:table/test-table",
     *       "DeletionProtectionEnabled":false
     *    }
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CreateTableResponse : public Dto::Common::BaseRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Table class
         */
        std::string tableClass;

        /**
         * Table name
         */
        std::string tableName;

        /**
         * Table ARN
         */
        std::string tableArn;

        /**
         * Table size
         */
        long tableSizeBytes;

        /**
         * Item count
         */
        long itemCount;

        /**
         * Delete protection enabled
         */
        bool deleteProtectionEnabled;

        /**
         * Key schema
         */
        std::map<std::string, std::string> keySchemas;

        /**
         * Tags
         */
        std::map<std::string, std::string> tags;

        /**
         * Attribute definitions
         */
        std::map<std::string, std::string> attributes;

        /**
         * Table status
         */
        TableStatusType tableStatus;

        /**
         * Original HTTP response body
         */
        std::string body;

        /**
         * Original HTTP response headers
         */
        std::map<std::string, std::string> headers;

        /**
         * HTTP status from docker image
         */
        http::status status;

        /**
         * Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const CreateTableResponse &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_CREATE_TABLE_RESPONSE_H
