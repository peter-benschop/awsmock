//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_CREATE_EVENT_SOURCE_MAPPINGS_RESPONSE_H
#define AWSMOCK_DTO_LAMBDA_CREATE_EVENT_SOURCE_MAPPINGS_RESPONSE_H

// C++ standard includes
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/common/BaseRequest.h>
#include <awsmock/dto/lambda/model/Code.h>
#include <awsmock/dto/lambda/model/Environment.h>
#include <awsmock/dto/lambda/model/EphemeralStorage.h>

namespace AwsMock::Dto::Lambda {

    /**
     * @brief Create event source mapping response
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
     *   "LastModified": number,
     *   "LastProcessingResult": "string",
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
     *   "State": string,
     *   "StateTransitionReason": string,
     *   "Topics": [ "string" ],
     *   "TumblingWindowInSeconds": number
     *   "UUID": string
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct CreateEventSourceMappingsResponse : public Dto::Common::BaseRequest {

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
         * UUID
         */
        std::string uuid;

        /**
         * Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Parse a JSON stream.
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
        friend std::ostream &operator<<(std::ostream &os, const CreateEventSourceMappingsResponse &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_CREATE_EVENT_SOURCE_MAPPINGS_RESPONSE_H
