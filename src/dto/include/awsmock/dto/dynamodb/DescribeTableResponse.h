//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_DESCRIBE_TABLE_RESPONSE_H
#define AWSMOCK_DTO_DYNAMODB_DESCRIBE_TABLE_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/dynamodb/ProvisionedThroughput.h>
#include <awsmock/dto/dynamodb/TableStatus.h>

namespace AwsMock::Dto::DynamoDb {

    /**
     * DynamoDB describe table response
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct DescribeTableResponse {

        /**
         * Region
         */
        std::string region;

        /**
         * Table name
         */
        std::string tableName;

        /**
         * Table ID
         */
        std::string tableId;

        /**
         * Table ARN
         */
        std::string tableArn;

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
         * Provisioned throughput
         */
        ProvisionedThroughput provisionedThroughput;

        /**
         * Table status
         */
        TableStatus tableStatus;

        /**
         * HTTP response body
         */
        std::string body;

        /**
         * HTTP response headers
         */
        std::map<std::string, std::string> headers;

        /**
         * HTTP status from docker image
         */
        Poco::Net::HTTPResponse::HTTPStatus status;

        /**
         * Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Parse a JSON stream
         *
         * @param body JSON string
         * @param headers map of headers
         */
        void FromJson(const std::string &body, const std::map<std::string, std::string> &headers);

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
        friend std::ostream &operator<<(std::ostream &os, const DescribeTableResponse &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_DESCRIBE_TABLE_RESPONSE_H
