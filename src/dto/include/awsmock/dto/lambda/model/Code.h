//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_CODE_H
#define AWSMOCK_DTO_LAMBDA_CODE_H

// C++ standard includes
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/lambda/model/Environment.h>
#include <awsmock/dto/lambda/model/EphemeralStorage.h>

namespace AwsMock::Dto::Lambda {

    /**
     * Lambda code DTO
     *
     * Example:
     * @code{.json}
     * "Code": {
     *    "ImageUri": "string",
     *    "Location": "string",
     *    "RepositoryType": "string",
     *    "ResolvedImageUri": "string"
     * }
     * @endcode
     */
    struct Code {

        /**
         * Image URI
         */
        std::string imageUri;

        /**
         * Location
         */
        std::string location;

        /**
         * S3 bucket
         */
        std::string s3Bucket;

        /**
         * S3 key
         */
        std::string s3Key;

        /**
         * S3 object version
         */
        std::string s3ObjectVersion;

        /**
         * Zipped function code.
         *
         * <p>The base64-encoded contents of the deployment package. AWS SDK and AWS CLI clients handle the encoding for you.</p>
         */
        std::string zipFile;

        /**
         * Repository
         */
        std::string repositoryType;

        /**
         * Resolved image URI
         */
        std::string resolvedImageUri;

        /**
         * Convert from a JSON object.
         *
         * @param jsonObject json object
         */
        void FromJson(const Poco::JSON::Object::Ptr &jsonObject);

        /**
         * Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
        friend std::ostream &operator<<(std::ostream &os, const Code &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_CODE_H
