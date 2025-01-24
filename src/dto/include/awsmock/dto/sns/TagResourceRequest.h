//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_TAG_RESOURCE_REQUEST_H
#define AWSMOCK_DTO_SNS_TAG_RESOURCE_REQUEST_H

// C++ standard includes
#include <map>
#include <string>

// Awsmock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/StringUtils.h>

namespace AwsMock::Dto::SNS {

    struct TagResourceRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Resource ARN (topic ARN)
         */
        std::string resourceArn;

        /**
         * Tags map
         */
        std::map<std::string, std::string> tags;

        /**
         * @brief Convert to JSON representation
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
        friend std::ostream &operator<<(std::ostream &os, const TagResourceRequest &r);
    };

    typedef std::map<std::string, std::string> TagList;

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_TAG_RESOURCE_REQUEST_H
