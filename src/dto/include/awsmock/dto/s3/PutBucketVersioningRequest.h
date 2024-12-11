//
// Created by vogje01 on 13/10/2023.
//

#ifndef AWSMOCK_CORE_DTO_PUT_BUCKET_VERSIONING_REQUEST_H
#define AWSMOCK_CORE_DTO_PUT_BUCKET_VERSIONING_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

namespace AwsMock::Dto::S3 {

    struct PutBucketVersioningRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * AWS user
         */
        std::string user;

        /**
         * Bucket name
         */
        std::string bucket;

        /**
         * Status
         */
        std::string status;

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
        friend std::ostream &operator<<(std::ostream &os, const PutBucketVersioningRequest &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_CORE_DTO_PUT_BUCKET_VERSIONING_REQUEST_H
