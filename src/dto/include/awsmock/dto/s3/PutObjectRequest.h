//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_PUTOBJECTREQUEST_H
#define AWSMOCK_CORE_DTO_PUTOBJECTREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <map>

namespace AwsMock::Dto::S3 {

  struct PutObjectRequest {

    /**
     * Region
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
     * Owner
     */
    std::string owner;

    /**
     * MD5 sum
     */
    std::string md5Sum;

    /**
     * Content type
     */
    std::string contentType;

    /**
     * Content type
     */
    long contentLength;

    /**
     * Checksum algorithm
     */
    std::string checksumAlgorithm;

    /**
     * Metadata
     */
    std::map<std::string, std::string> metadata;

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
    friend std::ostream &operator<<(std::ostream &os, const PutObjectRequest &r);

  };

} // namespace AwsMock::Dto::s3

#endif //AWSMOCK_CORE_DTO_PUTOBJECTREQUEST_H
