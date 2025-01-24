//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_CREATE_EVENT_SOURCE_MAPPINGS_REQUEST_H
#define AWSMOCK_DTO_LAMBDA_CREATE_EVENT_SOURCE_MAPPINGS_REQUEST_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Lambda {

    /**
     * @brief Create event source mapping request
     *
     * Example:
     * @code{.json}
     * {
     *   "AmazonManagedKafkaEventSourceConfig": {
     *     "ConsumerGroupId": "string"
     *   },
     *   "BatchSize": number,
     *   "BisectBatchOnFunctionError": boolean,
     *   "DestinationConfig": {
     *     "OnFailure": {
     *       "Destination": "string"
     *     },
     *     "OnSuccess": {
     *       "Destination": "string"
     *     }
     *   },
     *   "DocumentDBEventSourceConfig": {
     *     "CollectionName": "string",
     *     "DatabaseName": "string",
     *     "FullDocument": "string"
     *   },
     *   "Enabled": boolean,
     *   "EventSourceArn": "string",
     *   "FilterCriteria": {
     *     "Filters": [
     *       {
     *         "Pattern": "string"
     *       }
     *     ]
     *   },
     *   "FunctionName": "string",
     *   "FunctionResponseTypes": [ "string" ],
     *   "MaximumBatchingWindowInSeconds": number,
     *   "MaximumRecordAgeInSeconds": number,
     *   "MaximumRetryAttempts": number,
     *   "ParallelizationFactor": number,
     *   "Queues": [ "string" ],
     *   "ScalingConfig": {
     *     "MaximumConcurrency": number
     *   },
     *   "SelfManagedEventSource": {
     *     "Endpoints": {
     *       "string" : [ "string" ]
     *     }
     *   },
     *   "SelfManagedKafkaEventSourceConfig": {
     *     "ConsumerGroupId": "string"
     *   },
     *   "SourceAccessConfigurations": [
     *     {
     *       "Type": "string",
     *       "URI": "string"
     *     }
     *   ],
     *   "StartingPosition": "string",
     *   "StartingPositionTimestamp": number,
     *   "Topics": [ "string" ],
     *   "TumblingWindowInSeconds": number
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CreateEventSourceMappingsRequest : public Dto::Common::BaseRequest {

        /**
         * Name of the function
         */
        std::string functionName;

        /**
         * Event source ARN
         */
        std::string eventSourceArn;

        /**
         * Batch size
         */
        int batchSize;

        /**
         * Batch size
         */
        int maximumBatchingWindowInSeconds;

        /**
         * Enabled
         */
        bool enabled = true;

        /**
         * Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Parse a JSON stream.
         *
         * @code{.json}
         *"{\"JAVA_TOOL_OPTIONS\":\"-Duser.timezone=Europe/Berlin -Dspring.profiles.active=localhost\"}"
         * @endcode
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const CreateEventSourceMappingsRequest &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_CREATE_EVENT_SOURCE_MAPPINGS_REQUEST_H
