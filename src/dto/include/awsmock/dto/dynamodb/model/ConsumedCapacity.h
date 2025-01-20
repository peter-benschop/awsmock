//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_CONSUMED_CAPACITY_H
#define AWSMOCK_DTO_DYNAMODB_CONSUMED_CAPACITY_H

// C++ standard includes
#include <chrono>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::DynamoDb {

    using std::chrono::system_clock;

    /**
     * DynamoDB provisioned throughput
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ConsumedCapacity {

        /**
         * Table name
         */
        std::string tableName;

        /**
         * Read capacity units
         */
        int readCapacityUnits = 0;

        /**
         * Write capacity units
         */
        int writeCapacityUnits = 0;

        /**
         * Converts the entity to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert to a BSON document
         */
        bsoncxx::document::view ToDocument() const;

        /**
         * @brief Convert from a BSON document
         */
        void FromDocument(bsoncxx::document::view document);

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
        friend std::ostream &operator<<(std::ostream &os, const ConsumedCapacity &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_CONSUMED_CAPACITY_H
