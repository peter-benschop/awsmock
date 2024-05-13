//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_S3_LIST_OBJECT_VERSIONS_REQUEST_H
#define AWSMOCK_DTO_S3_LIST_OBJECT_VERSIONS_REQUEST_H

// C++ Standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Dto::S3 {

    /**
     * @brief List object version request
     *
     * @author jens.vogt\@opitz-consulting.com
     */
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
         * Delimiter
         */
        std::string delimiter;

        /**
         * Encoding type
         */
        std::string encodingType;

        /**
         * Page size
         */
        int pageSize;

        /**
         * Maximal number of keys
         */
        int maxKeys;

        /**
         * Version ID marker
         */
        std::string versionIdMarker;

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

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_LIST_OBJECT_VERSIONS_REQUEST_H
