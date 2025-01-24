//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SSM_DESCRIBE_PARAMETERS_RESPONSE_H
#define AWSMOCK_DTO_SSM_DESCRIBE_PARAMETERS_RESPONSE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/dto/ssm/model/Parameter.h>

namespace AwsMock::Dto::SSM {

    struct DescribeParametersResponse {

        /**
         * AWS region
         */
        std::string region;

        /**
         * The token to use when requesting the next set of items.
         */
        std::string nextToken;

        /**
         * Parameters returned by the request.
         */
        std::vector<Parameter> parameters;

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
        friend std::ostream &operator<<(std::ostream &os, const DescribeParametersResponse &r);
    };

}// namespace AwsMock::Dto::SSM

#endif// AWSMOCK_DTO_SSM_DESCRIBE_PARAMETERS_RESPONSE_H
