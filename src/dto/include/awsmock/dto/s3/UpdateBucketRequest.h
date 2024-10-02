//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_UPDATE_BUCKET_REQUEST_H
#define AWSMOCK_DTO_S3_UPDATE_BUCKET_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include "awsmock/dto/s3/model/Bucket.h"
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::S3 {

    /**
     * @brief Update bucket request
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct UpdateBucketRequest {

        /**
         * Bucket
         */
        Bucket bucket;

        /**
         * @brief Parse values from a JSON stream
         *
         * @param body json input stream
         */
        static UpdateBucketRequest FromJson(const std::string &body);

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
        friend std::ostream &operator<<(std::ostream &os, const UpdateBucketRequest &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_UPDATE_BUCKET_REQUEST_H
