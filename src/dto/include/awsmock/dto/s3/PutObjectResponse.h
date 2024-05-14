//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_PUT_OBJECT_RESPONSE_H
#define AWSMOCK_CORE_DTO_PUT_OBJECT_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include "awsmock/core/exception/JsonException.h"
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>

namespace AwsMock::Dto::S3 {

    struct PutObjectResponse {

        /**
         * Bucket
         */
        std::string bucket;

        /**
         * Key
         */
        std::string key;

        /**
         * ETag
         */
        std::string etag = {};

        /**
         * Base64 encoded MD5 sum
         */
        std::string md5Sum = {};

        /**
         * Content length
         */
        long contentLength;

        /**
         * Base64 encoded SHA1 checksum
         */
        std::string checksumSha1 = {};

        /**
         * Base64 encoded SHA256 checksum
         */
        std::string checksumSha256 = {};

        /**
         * Metadata
         */
        std::map<std::string, std::string> metadata;

        /**
         * Version ID
         */
        std::string versionId;

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
        friend std::ostream &operator<<(std::ostream &os, const PutObjectResponse &p);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_CORE_DTO_PUT_OBJECT_RESPONSE_H
