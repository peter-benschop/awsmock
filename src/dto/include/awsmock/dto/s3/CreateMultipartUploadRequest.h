//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_S3_CREATE_MULTIPART_UPLOAD_REQUEST_H
#define AWSMOCK_CORE_DTO_S3_CREATE_MULTIPART_UPLOAD_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::S3 {

    struct CreateMultipartUploadRequest {

        /**
         * Bucket location
         */
        std::string region;

        /**
         * Bucket name
         */
        std::string bucket;

        /**
         * Bucket owner
         */
        std::string key;

        /**
         * AWS user
         */
        std::string user;

        /**
         * AWS upload ID
         */
        std::string uploadId;

        /**
         * Metadata
         */
        std::map<std::string, std::string> metadata;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Convert from XML representation
         *
         * @param xmlString XML string
         */
        void FromXml(const std::string &xmlString);

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
        friend std::ostream &operator<<(std::ostream &os, const CreateMultipartUploadRequest &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_CORE_DTO_S3_CREATE_MULTIPART_UPLOAD_REQUEST_H
