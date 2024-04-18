//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LIST_OBJECT_VERSIONS_REQUEST_H
#define AWSMOCK_DTO_S3_LIST_OBJECT_VERSIONS_REQUEST_H

// C++ Standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/JsonException.h>

namespace AwsMock::Dto::S3 {

  struct ListObjectVersionsRequest {

    /**
     * Region
     */
    std::string region;

    /**
     * Bucket name
     */
    std::string bucket;

    /**
     * Prefix
     */
    std::string prefix;

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
    friend std::ostream &operator<<(std::ostream &os, const ListObjectVersionsRequest &r);

  };

} // namespace AwsMock::Dto::S3

#endif // AWSMOCK_DTO_S3_LIST_OBJECT_VERSIONS_REQUEST_H
