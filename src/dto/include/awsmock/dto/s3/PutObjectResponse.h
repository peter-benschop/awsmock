//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_PUTOBJECTRESPONSE_H
#define AWSMOCK_CORE_DTO_PUTOBJECTRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"

namespace AwsMock::Dto::S3 {

  struct PutObjectResponse {

    /**
     * Bucket
     */
    std::string bucket;

    /**
     * Key
     */
    std::string key;

    /**
     * ETag
     */
    std::string etag;

    /**
     * Base64 encoded MD5 sum
     */
    std::string md5Sum;

    /**
     * Content length
     */
    long contentLength;

    /**
     * SHA256 checksum algorithm
     */
    std::string checksumAlgorithm = "SHA256";

    /**
     * Base64 encoded SHA256 checksum
     */
    std::string checksumSha256;

    /**
     * Metadata
     */
    std::map<std::string, std::string> metadata;

    /**
     * Version ID
     */
    std::string versionId;

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    std::string ToString() const;

    /**
     * Stream provider.
     *
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const PutObjectResponse &p);

  };

} // namespace AwsMock::Dto::S3

#endif //AWSMOCK_CORE_DTO_PUTOBJECTRESPONSE_H
