//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_S3_CONTENT_H
#define AWSMOCK_DTO_S3_CONTENT_H

// C++ includes
#include <sstream>
#include <string>
#include <vector>

// AwsMock includes
#include "Owner.h"
#include "awsmock/core/JsonException.h"
#include "awsmock/core/JsonUtils.h"
#include "awsmock/core/LogStream.h"
#include "awsmock/core/XmlUtils.h"

namespace AwsMock::Dto::S3 {

    struct Content {

        /**
         * Checksum algorithms
         */
        std::vector<std::string> checksumAlgorithms;

        /**
         * ETag
         */
        std::string etag;

        /**
         * Key
         */
        std::string key;

        /**
         * Owner
         */
        Owner owner;

        /**
         * Size
         */
        long size = 0;

        /**
         * Storage class
         */
        std::string storageClass;

        /**
         * Last modified
         */
        std::string lastModified;

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
        friend std::ostream &operator<<(std::ostream &os, const Content &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_CONTENT_H
