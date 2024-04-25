//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_GET_METADATA_REQUEST_H
#define AWSMOCK_DTO_S3_GET_METADATA_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>

namespace AwsMock::Dto::S3 {

    struct GetMetadataRequest {

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
        friend std::ostream &operator<<(std::ostream &os, const GetMetadataRequest &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_GET_METADATA_REQUEST_H
