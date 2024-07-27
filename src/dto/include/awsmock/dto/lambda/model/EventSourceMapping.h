//
// Created by vogje01 on 7/13/24.
//

#ifndef AWSMOCK_DTO_LAMBDA_EVENT_SOURCE_MAPPING_H
#define AWSMOCK_DTO_LAMBDA_EVENT_SOURCE_MAPPING_H


// C++ standard includes
#include <chrono>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>

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
         * Creates a JSON object.
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
        friend std::ostream &operator<<(std::ostream &os, const EventSourceMapping &r);
    };
}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_EVENT_SOURCE_MAPPING_H
