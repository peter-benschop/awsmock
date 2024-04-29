//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LIST_BUCKET_REQUEST_H
#define AWSMOCK_DTO_S3_LIST_BUCKET_REQUEST_H

// C++ Standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>

namespace AwsMock::Dto::S3 {

    struct ListBucketRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Name
         */
        std::string name;

        /**
         * List type
         */
        int listType;

        /**
         * Prefix
         */
        std::string prefix;

        /**
         * Delimiter
         */
        std::string delimiter;

        /**
         * Encoding type
         */
        std::string encodingType;

        /**
         * Convert to a JSON string
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
        friend std::ostream &operator<<(std::ostream &os, const ListBucketRequest &r);
    };

}// namespace AwsMock::Dto::S3

#endif//AWSMOCK_DTO_S3_LIST_BUCKET_REQUEST_H
