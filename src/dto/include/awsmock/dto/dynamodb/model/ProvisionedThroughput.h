//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_PROVISIONED_THROUGHPUT_H
#define AWSMOCK_DTO_DYNAMODB_PROVISIONED_THROUGHPUT_H

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
    struct ProvisionedThroughput {

        /**
         * Read capacity units
         */
        int readCapacityUnits = 0;

        /**
         * Write capacity units
         */
        int writeCapacityUnits = 0;

        /**
         * Last decrease time
         */
        system_clock::time_point lastDecreaseDateTime;

        /**
         * Last increase time
         */
        system_clock::time_point lastIncreaseDateTime;

        /**
         * NUmber of decreases
         */
        long numberOfDecreasesToday = 0;

        /**
         * @brief Converts the entity to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert to a BSON document
         */
        view_or_value<view, value> ToDocument() const;

        /**
         * @brief Convert from a BSON document
         */
        void FromDocument(view_or_value<view, value> document);

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as JSON string
         */
        std::string ToJson();

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const ProvisionedThroughput &r);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_DYNAMODB_PROVISIONED_THROUGHPUT_H
