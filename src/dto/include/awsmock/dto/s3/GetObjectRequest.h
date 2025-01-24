//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_GET_OBJECT_REQUEST_H
#define AWSMOCK_DTO_S3_GET_OBJECT_REQUEST_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::S3 {

    /**
     * @brief Get object request
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct GetObjectRequest {

        /**
         * AWS region name
         */
        std::string region;

        /**
         * Bucket
         */
        std::string bucket;

        /**
         * Key
         */
        std::string key;

        /**
         * Version ID
         */
        std::string versionId;

        /**
         * Range minimum
         */
        long min;

        /**
         * Range maximum
         */
        long max;

        /**
         * Convert to a JSON string
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
        friend std::ostream &operator<<(std::ostream &os, const GetObjectRequest &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_GET_OBJECT_REQUEST_H
