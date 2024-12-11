//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SSM_DESCRIBE_PARAMETERS_REQUEST_H
#define AWSMOCK_DTO_SSM_DESCRIBE_PARAMETERS_REQUEST_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/ssm/model/ParameterFilter.h>

namespace AwsMock::Dto::SSM {

    struct DescribeParametersRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Filters to limit the request results.
         */
        std::vector<ParameterFilter> parameterFilters;

        /**
         * The maximum number of items to return for this call. The call also returns a token that you can specify in a subsequent call to get the next set of results.
         */
        int maxResults;

        /**
         * The token for the next set of items to return. (You received this token from a previous call.)
         */
        std::string nextToken;

        /**
         * AWS request ID
         */
        std::string requestId;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the JSON string to DTO.
         *
         * @param jsonString JSON string
         */
        void FromJson(const std::string &jsonString);

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const DescribeParametersRequest &r);
    };

}// namespace AwsMock::Dto::SSM

#endif// AWSMOCK_DTO_SSM_DESCRIBE_PARAMETERS_REQUEST_H
