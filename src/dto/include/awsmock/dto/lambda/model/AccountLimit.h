//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_ACCOUNT_LIMIT_H
#define AWSMOCK_DTO_LAMBDA_ACCOUNT_LIMIT_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/common/BaseRequest.h>

namespace AwsMock::Dto::Lambda {

    /**
     * @brief Create function response
     *
     * Example:
     * @code{.json}
     * "AccountLimit": {
     *   "CodeSizeUnzipped": number,
     *   "CodeSizeZipped": number,
     *   "ConcurrentExecutions": number,
     *   "TotalCodeSize": number,
     *   "UnreservedConcurrentExecutions": number
     * }
     * @endcode
     *
     * @author jens.vogt\@opitz--consulting.com
     */
    struct AccountLimit : Common::BaseRequest {

        /**
         * Code size unzipped limit
         */
        long codeSizeUnzipped{};

        /**
         * Code size zipped limit
         */
        long codeSizeZipped{};

        /**
         * Concurrent executions
         */
        int concurrentExecutions{};

        /**
         * Total code size
         */
        long totalCodeSize{};

        /**
         * Unreserved concurrent executions
         */
        long unreservedConcurrentExecutions{};

        /**
         * @brief Convert to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const AccountLimit &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_ACCOUNT_LIMIT_H
