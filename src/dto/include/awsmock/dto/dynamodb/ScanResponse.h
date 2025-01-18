//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_SCAN_RESPONSE_H
#define AWSMOCK_DTO_DYNAMODB_SCAN_RESPONSE_H

// C++ standard includes
#include <string>

// Boost include<
#include <boost/beast.hpp>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/BaseRequest.h>
#include <awsmock/dto/dynamodb/model/TableStatus.h>

namespace AwsMock::Dto::DynamoDb {

    namespace http = boost::beast::http;

    /**
     * @brief Scan response
     *
     * Example:
     * @code{.json}
     * {
     *   "ConsumedCapacity":
     *     {
     *       "TableName":"test-table",
     *       "CapacityUnits":1.0
     *     }
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ScanResponse : Common::BaseRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Table name
         */
        std::string tableName;

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
         * @brief Scans the response and fills in the attributes
         */
        void PrepareResponse();

        /**
         * Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Parse a JSON stream
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

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
        friend std::ostream &operator<<(std::ostream &os, const ScanResponse &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_SCAN_RESPONSE_H
