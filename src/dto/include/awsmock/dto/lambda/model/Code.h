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
     * @brief Lambda code DTO
     *
     * Example:
     * @code{.json}
     * "Code": {
     *   "ImageUri": "string",
     *   "S3Bucket": "string",
     *   "S3Key": "string",
     *   "S3ObjectVersion": "string",
     *   "ZipFile": blob
     * },
     * @endcode
     *
     */
    struct Code {

        /**
         * URI of a container image in the Amazon ECR registry.
         */
        std::string imageUri;

        /**
         * An Amazon S3 bucket in the same AWS Region as your function. The bucket can be in a different AWS account.
         */
        std::string s3Bucket;

        /**
         * The Amazon S3 key of the deployment package.
         */
        std::string s3Key;

        /**
         * For versioned objects, the version of the deployment package object to use.
         */
        std::string s3ObjectVersion;

        /**
         * Zipped function code.
         *
         * @par
         * The base64-encoded contents of the deployment package. AWS SDK and AWS CLI clients handle the encoding for you.
         */
        std::string zipFile{};

        /**
         * Repository
         */
        std::string repositoryType;

        /**
         * Resolved image URI
         */
        std::string resolvedImageUri;

        /**
         * @brief Convert from a JSON object.
         *
         * @param jsonObject json object
         */
        void FromJson(const Poco::JSON::Object::Ptr &jsonObject);

        /**
         * @brief Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Creates a JSON string from the object.
         *
         * @return JSON string
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
        friend std::ostream &operator<<(std::ostream &os, const Code &r);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_CODE_H
