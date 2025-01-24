//
// Created by vogje01 on 7/13/24.
//

#ifndef AWSMOCK_DTO_LAMBDA_EVENT_SOURCE_MAPPING_H
#define AWSMOCK_DTO_LAMBDA_EVENT_SOURCE_MAPPING_H


// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::Lambda {

    struct EventSourceMapping {

        /**
         * AWS region
         */
        std::string region;

        /**
         * AWS user
         */
        std::string user;

        /**
         * Event source ARN
         */
        std::string eventSourceArn;

        /**
         * Function ARN
         */
        std::string functionArn;

        /**
         * Batch size
         */
        int batchSize;

        /**
         * Maximal batches in windows
         */
        int maximumBatchingWindowInSeconds;

        /**
         * UUID
         */
        std::string uuid;

        /**
         * @brief Creates a JSON object.
         *
         * @return JSON object
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const EventSourceMapping &r);
    };
}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_EVENT_SOURCE_MAPPING_H
