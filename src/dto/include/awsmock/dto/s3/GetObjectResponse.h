//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_GET_OBJECT_RESPONSE_H
#define AWSMOCK_DTO_S3_GET_OBJECT_RESPONSE_H

// C++ standard includes
#include <chrono>
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::S3 {

    using std::chrono::system_clock;

    /**
     * @brief Get object response
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct GetObjectResponse {

        /**
         * AWS region
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
         * Content length
         */
        long size;

        /**
         * File name
         */
        std::string filename;

        /**
         * Content type
         */
        std::string contentType;

        /**
         * Metadata
         */
        std::map<std::string, std::string> metadata;

        /**
         * MD5 sum
         */
        std::string md5sum;

        /**
         * Created
         */
        system_clock::time_point created;

        /**
         * Modified
         */
        system_clock::time_point modified;

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
        friend std::ostream &operator<<(std::ostream &os, const GetObjectResponse &r);
    };

}// namespace AwsMock::Dto::S3

#endif//AWSMOCK_DTO_S3_GET_OBJECT_RESPONSE_H
