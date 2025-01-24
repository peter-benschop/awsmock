//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_LIST_EVENT_SOURCE_MAPPINGS_RESPONSE_H
#define AWSMOCK_DTO_LAMBDA_LIST_EVENT_SOURCE_MAPPINGS_RESPONSE_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/BaseRequest.h>
#include <awsmock/dto/lambda/model/EventSourceMapping.h>

namespace AwsMock::Dto::Lambda {

    /**
     * @brief List event source mapping response.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct ListEventSourceMappingsResponse : Common::BaseRequest {

        /**
         * List of event source mappings.
         */
        std::vector<EventSourceMapping> eventSourceMappings;

        /**
         * Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const ListEventSourceMappingsResponse &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_LIST_EVENT_SOURCE_MAPPINGS_RESPONSE_H
